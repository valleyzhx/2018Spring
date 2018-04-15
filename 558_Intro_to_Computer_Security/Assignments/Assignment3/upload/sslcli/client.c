#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define kLength 1024

int  _sockfd;
SSL_CTX *_sslctx;
SSL *_cSSL;


#pragma mark- SSL
void InitializeSSL()
{
    SSL_load_error_strings();
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    _sslctx = SSL_CTX_new( SSLv23_client_method());
    SSL_CTX_set_options(_sslctx, SSL_OP_SINGLE_DH_USE);
    if (_sslctx == NULL)
    {
        ERR_print_errors_fp(stdout);
        exit(1);
    }
}

void DestroySSL()
{
    ERR_free_strings();
    EVP_cleanup();
}

void ShutdownSSL()
{
    SSL_shutdown(_cSSL);
    SSL_free(_cSSL);
}


void releaseConnection(){
    DestroySSL();
    ShutdownSSL();
    close(_sockfd);
}

void intHandler(int dummy){
    releaseConnection();
    exit(0);
}


int main(int argc, char **argv) {
    //signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, intHandler);

    
    ssize_t read_n;
    char recvline[kLength];
    struct sockaddr_in servaddr;
    struct hostent *he;
    
    if(argc!=3){
        printf("Usage : gettime <IP address>\n");
        exit(1);
    }
    
    if ((he = gethostbyname(argv[1])) == NULL) {  // get the host info
        perror("gethostbyname");
        exit(2);
    }
    
    InitializeSSL();//initial SSL

    /* Create a TCP socket */
    if((_sockfd=socket(AF_INET,SOCK_STREAM, 0)) < 0){
        perror("socket"); exit(3);}
    
    /* Specify server’s IP address and port */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2])); /* daytime server port */
    
    if (inet_pton(AF_INET, inet_ntoa(*(struct in_addr *)he->h_addr_list[0]), &servaddr.sin_addr) <= 0) {
        perror("inet_pton"); exit(4);
    }
    
    /* Connect to the server */
    if (connect(_sockfd,  (struct sockaddr *) &servaddr,sizeof(servaddr)) < 0 ) {
        perror("connect"); exit(5);
    }
    _cSSL = SSL_new(_sslctx);
    SSL_set_fd(_cSSL, _sockfd);
    int ssl_err = SSL_connect(_cSSL);
    if(ssl_err <= 0)
    {
        ERR_print_errors_fp(stdout);
        releaseConnection();
        exit(1);
    }
    while (1) {
        
        /* Read the date/time from socket */
        while ( (read_n = SSL_read(_cSSL, recvline, kLength)) >= 0) {
            //recvline[read_n] = '\0';        /* null terminate */
            if (read_n == 0) {// exit
                releaseConnection();
                exit(1);
            }
            printf("%s", recvline);
            if (strcmp(recvline, "OK\n")==0) {
                printf("the password is correct\n");
                releaseConnection();
                exit(0);
            }
            if (strcmp(recvline, "password is incorrect\n")==0) {
                releaseConnection();
                exit(0);
            }
            
            /*write command to server*/
            char input[100];
            printf("sslserv>");
            fgets(input,100,stdin);
            if (strcmp(input,"exit\n")==0) {// exit
                releaseConnection();
                exit(0);
            }
            SSL_write(_cSSL, input, (int)strlen(input));
            memset(recvline,0,kLength);
        }
        if (read_n < 0) { perror("read"); releaseConnection();exit(6); }

    }
    
    
    return 0;
}

