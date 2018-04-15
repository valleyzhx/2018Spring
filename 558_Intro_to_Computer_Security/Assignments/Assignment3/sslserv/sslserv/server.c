#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include "gen-pass.h"
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

typedef enum {
    InputModeUserId,
    InputModePassword,
} InputMode;

char _userId[100];
char _password[100];


int _connfd;
SSL_CTX *_sslctx;
SSL *_cSSL;
InputMode _inputMode;

void realseConnection(void);

void service_client(){
    ssize_t read_n;
    char recvline[200];
    while ( (read_n = SSL_read(_cSSL, recvline, 200)) >= 0) {
        printf("%s", recvline);        
        if (read_n == 0 ) {// exit
            printf("exit");
            realseConnection();
            exit(1);
        }else if (read_n < 0) {
            perror("read");
            realseConnection();
            exit(5);
        }else{
            char last = recvline[strlen(recvline)-1];
            if (last == '\n') {
                recvline[strlen(recvline)-1] = '\0';
            }
            char buffer[1000]={'\0'};
            
            if (_inputMode == InputModeUserId) {
                memset(_userId, 0, 100);
                for (int i=0; i<strlen(recvline); i++) {
                    if (recvline[i] == '\n') {
                        break;
                    }
                    _userId[i] = recvline[i];
                }
                if (checkExisting(_userId)){
                    strcpy(buffer, "please input your password:\n");
                    _inputMode = InputModePassword;
                }else{
                    strcpy(buffer, "userId not exist!\nplease input your userId:\n");
                }
                
            }else if (_inputMode == InputModePassword){
                memset(_password, 0, 100);
                for (int i=0; i<strlen(recvline); i++) {
                    if (recvline[i] == '\n') {
                        break;
                    }
                    _password[i] = recvline[i];
                }
                if (verifyUser(_userId, _password)) {
                    strcpy(buffer, "OK\n");
                    _inputMode = InputModeUserId;
                }else{
                    strcpy(buffer, "password is incorrect\n");
                }
            }
            buffer[strlen(buffer)] = '\0';
            SSL_write(_cSSL, buffer, (int)strlen(buffer));
        }
        memset(recvline,0,200);
    }
    
}

#pragma mark- SSL
void InitializeSSL()
{
    SSL_load_error_strings();
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    _sslctx = SSL_CTX_new( SSLv23_server_method());
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
    if (_cSSL) {
        SSL_free(_cSSL);
    }
    
}


void realseConnection(){
    DestroySSL();
    ShutdownSSL();
    close(_connfd);
}


void intHandler(int dummy){
    realseConnection();
    exit(0);
}

int main(int argc, char **argv) {
    signal(SIGINT, intHandler);

    int   listenfd;
    socklen_t clilen;
    struct sockaddr_in servaddr, cliaddr;
    if(argc!=2){
        printf("need port number!\n");
        exit(1);
    }
   
    InitializeSSL();//initial SSL
    
    int use_cert = SSL_CTX_use_certificate_file(_sslctx, "./certificate/certificate.pem" , SSL_FILETYPE_PEM);
    if (use_cert<=0) {
        ERR_print_errors_fp(stdout);
        exit(1);
    }
    
    int use_prv = SSL_CTX_use_PrivateKey_file(_sslctx, "./certificate/key.pem", SSL_FILETYPE_PEM);
    if (use_prv<=0) {
        ERR_print_errors_fp(stdout);
        exit(1);
    }
    if (!SSL_CTX_check_private_key(_sslctx))//checking the prv key
    {
        ERR_print_errors_fp(stdout);
        exit(1);
    }
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    int port = atoi(argv[1]);
    servaddr.sin_port        = htons(port);
    
    bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    listen(listenfd, 100);
    
    clilen = sizeof(cliaddr);
    _connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
    /*SSl Connection Build*/
    _cSSL = SSL_new(_sslctx);
    SSL_set_fd(_cSSL, _connfd );
  
    for ( ; ; ) {

        clilen = sizeof(cliaddr);
        int err = SSL_accept(_cSSL);
        if(err == -1){
            ERR_print_errors_fp(stdout);
            exit(1);
        }else{

            char *str = "please input your userId:\n";
            int len = SSL_write(_cSSL, str, (int)strlen(str));
            if (len<=0) {
                perror("ssl write");
                exit(errno);
            }
            service_client();
        }
        

    }
}

