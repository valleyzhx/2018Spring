#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#define kLength 1000

int  _sockfd;

void intHandler(int dummy){
    close(_sockfd);
    exit(0);
}


int main(int argc, char **argv) {
    //signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, intHandler);

    
    ssize_t read_n;
    char recvline[kLength];
    struct sockaddr_in servaddr;
    struct hostent *he;
    
    if(argc!=2){
        printf("Usage : gettime <IP address>");
        exit(1);
    }
    
    if ((he = gethostbyname(argv[1])) == NULL) {  // get the host info
        herror("gethostbyname");
        exit(2);
    }
    
    /* Create a TCP socket */
    if((_sockfd=socket(AF_INET,SOCK_STREAM, 0)) < 0){
        perror("socket"); exit(3);}
    
    /* Specify server’s IP address and port */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(10000); /* daytime server port */
    
    if (inet_pton(AF_INET, inet_ntoa(*(struct in_addr *)he->h_addr), &servaddr.sin_addr) <= 0) {
        perror("inet_pton"); exit(4);
    }
    
    /* Connect to the server */
    if (connect(_sockfd,  (struct sockaddr *) &servaddr,sizeof(servaddr)) < 0 ) {
        perror("connect"); exit(5);
    }
    
    while (1) {
        /* Read the date/time from socket */
        while ( (read_n = read(_sockfd, recvline, kLength)) >= 0) {
            //recvline[read_n] = '\0';        /* null terminate */
            if (read_n == 0) {// exit
                close(_sockfd);
                exit(1);
            }
            printf("%s", recvline);
            /*write command to server*/
            char input[100];
            printf("telnet>");
            fgets(input,100,stdin);
            if (strcmp(input,"exit\n")==0) {// exit
                close(_sockfd);
                exit(0);
            }
            write(_sockfd, input, strlen(input));
            memset(recvline,0,1000);
        }
        if (read_n < 0) { perror("read"); exit(6); }

    }
    
    return 0;
}

