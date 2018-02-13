#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
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
    
//    if(argc!=2){
//        printf("Usage : gettime <IP address>");
//        exit(1);
//    }
    
    /* Create a TCP socket */
    if((_sockfd=socket(AF_INET,SOCK_STREAM, 0)) < 0){
        perror("socket"); exit(2);}
    
    /* Specify server’s IP address and port */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(10000); /* daytime server port */
    
    if (inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0) {
        perror("inet_pton"); exit(3);
    }
    
    /* Connect to the server */
    if (connect(_sockfd,  (struct sockaddr *) &servaddr,sizeof(servaddr)) < 0 ) {
        perror("connect"); exit(4);
    }
    
    while (1) {
        /* Read the date/time from socket */
        memset(recvline,0,1000);
        while ( (read_n = read(_sockfd, recvline, kLength)) > 0) {
            recvline[read_n] = '\0';        /* null terminate */
            printf("%s", recvline);
            /*write command to server*/
            char input[100];
            printf("telnet>");
            fgets(input,100,stdin);
            write(_sockfd, input, strlen(input));
            if (strcmp(input,"exit\n")==0) {// exit
                close(_sockfd);
                exit(0);
            }
        }
        if (read_n < 0) { perror("read"); exit(5); }

    }
   
   
    
    return 0;
}

