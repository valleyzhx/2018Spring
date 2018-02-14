#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include "process.h"

void service_client(int connfd){
    ssize_t read_n;
    char recvline[100];
    while ( (read_n = read(connfd, recvline, 100)) > 0) {
        recvline[read_n] = '\0';        /* null terminate */
        printf("%s", recvline);
        /*perform command*/
        
        if (strcmp(recvline,"exit\n")==0) {// exit
            close(connfd);
            exit(0);
        }else{
            char buffer[100]={'\0'};
            int error = process(recvline,buffer);
            size_t length = strlen(buffer);
            if (length == 0) {
                buffer[length] = '\2';
            }
            buffer[strlen(buffer)] = '\0';
            
            /*write result to client*/
            write(connfd, buffer, strlen(buffer));
            
//            if(error){
//                close(connfd);
//                exit(6);
//            }
        }
    }
    if (read_n < 0) { perror("read"); close(connfd);exit(5); }
}



int main(int argc, char **argv) {
    int   listenfd, connfd;
    socklen_t clilen;
    struct sockaddr_in servaddr, cliaddr;
    char buff[100];
    time_t ticks;
    
    /* Create a TCP socket */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    /* Initialize server's address and well-known port */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(10000);   /* daytime server */
    
    /* Bind server’s address and port to the socket */
    bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    /* Convert socket to a listening socket – max 100 pending clients*/
    listen(listenfd, 100);
    
    for ( ; ; ) {
        /* Wait for client connections and accept them */
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
        /* Retrieve system time */
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        printf("%s\r\n", ctime(&ticks));
        /* Write to socket */
        write(connfd, buff, strlen(buff));
        
        service_client(connfd);
        
        
        /* Close the connection */
       // close(connfd);
    }
}

