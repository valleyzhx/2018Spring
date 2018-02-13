#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int  sockfd;
    ssize_t read_n;
    char recvline[100];
    struct sockaddr_in servaddr;
    
//    if(argc!=2){
//        printf("Usage : gettime <IP address>");
//        exit(1);
//    }
    
    /* Create a TCP socket */
    if((sockfd=socket(AF_INET,SOCK_STREAM, 0)) < 0){
        perror("socket"); exit(2);}
    
    /* Specify server’s IP address and port */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(10000); /* daytime server port */
    
    if (inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0) {
        perror("inet_pton"); exit(3);
    }
    
    /* Connect to the server */
    if (connect(sockfd,  (struct sockaddr *) &servaddr,sizeof(servaddr)) < 0 ) {
        perror("connect"); exit(4);
    }
    
    
    /* Read the date/time from socket */
    while ( (read_n = read(sockfd, recvline, 100)) > 0) {
        recvline[read_n] = '\0';        /* null terminate */
        printf("%s", recvline);
    }
    if (read_n < 0) { perror("read"); exit(5); }
    
    char input[100];
    while (1) {
        printf("telnet>");
        fgets(input,100,stdin);
        write(sockfd, input, strlen(input));
    }
    
   // close(sockfd);
}

