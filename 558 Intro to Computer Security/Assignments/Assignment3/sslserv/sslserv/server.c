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

int _connfd;

void intHandler(int dummy){
    close(_connfd);
    exit(0);
}


void service_client(){
    ssize_t read_n;
    char recvline[200];
    while ( (read_n = read(_connfd, recvline, 200)) >= 0) {
        printf("%s", recvline);        
        if (read_n == 0 ) {// exit
            printf("exit");
            close(_connfd);
            exit(1);
        }else{
            char buffer[1000]={'\0'};
            char userId[100]={'\0'};
            char password[100]={'\0'};
            char *temp = userId;
            int index = 0;
            for (int i=0; i<strlen(recvline); i++) {
                if (recvline[i]==' ') {
                    temp = password;
                    index = 0;
                }else if (recvline[i]=='\n'){
                    break;
                }
                else{
                    temp[index++] = recvline[i];
                }
            }
            
            FILE *fptr = fopen("password.txt", "a+");
            fseek(fptr,0,SEEK_SET);
            char savingStr[512] = {'\0'};
            bool exist = false;
            
            while(!feof(fptr)) {
                memset(savingStr, 0, 500);
                fgets(savingStr, sizeof(savingStr), fptr);
                char *savedUserId = strtok(savingStr, ",");
                if (savedUserId!=NULL) {
                    if (strcmp(userId,savedUserId)==0){
                        strcpy(buffer,"the ID already exists\n");
                        exist = true;
                        break;
                    }
                }
            }
            if (!exist) {
                time_t ticks = time(NULL);
                char savedTime[100]={'\0'};
                snprintf(savedTime, sizeof(savedTime), "%.24s", ctime(&ticks));
                char saving[1000] = {'\0'};
                char md5_pass[1024] = {'\0'};
                MD5_Encrypt(password, md5_pass);
                sprintf(saving, "%s,%s,%s\n", userId,md5_pass,savedTime);
                fputs(saving,fptr);
                strcpy(buffer,"Done!\n");
            }
            fclose(fptr);
            buffer[strlen(buffer)] = '\0';
            /*write result to client*/
            write(_connfd, buffer, strlen(buffer));
        }
        memset(recvline,0,200);
    }
    if (read_n < 0) { perror("read"); close(_connfd);exit(5); }
}


int main(int argc, char **argv) {
    signal(SIGINT, intHandler);

    int   listenfd;
    socklen_t clilen;
    struct sockaddr_in servaddr, cliaddr;
    if(argc!=2){
        printf("Usage : gettime <IP address>\n");
        exit(1);
    }
    /* Create a TCP socket */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    /* Initialize server's address and well-known port */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    int port = atoi(argv[1]);
    servaddr.sin_port        = htons(port);   /* daytime server */
    
    /* Bind server’s address and port to the socket */
    bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    /* Convert socket to a listening socket – max 100 pending clients*/
    listen(listenfd, 100);
    
    for ( ; ; ) {
        /* Wait for client connections and accept them */
        clilen = sizeof(cliaddr);
        _connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
        /* Retrieve system time */
//        ticks = time(NULL);
//        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
//        printf("%s\r\n", ctime(&ticks));
        char *str = "please input your userId and password, seperate by blank\n";
        /* Write to socket */
        write(_connfd, str, strlen(str));
        service_client();
        
        /* Close the connection */
       // close(_connfd);
    }
}

