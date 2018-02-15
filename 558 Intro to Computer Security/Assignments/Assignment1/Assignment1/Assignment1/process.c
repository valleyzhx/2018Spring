//
//  process.c
//  Assignment1
//
//  Created by Xiang on 2018/2/13.
//  Copyright © 2018年 Xiang. All rights reserved.
//

#include "process.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>

#define kLength 1000

int _latestPid = 0;

#pragma mark- write to pipe

void printString(char *string,char *result){
    printf("%s",string);
    strcpy(result, string);
}


#pragma mark- run command

int innerCommand(char *command[],char *result,int *error){
    if (strcmp(command[0],"pwd\0")==0){
        char buf[kLength]={'\0'};
        if ( getcwd(buf,sizeof(buf)) == NULL) {//get current dir
            printf("getcwd() error");
        }else{
            buf[strlen(buf)] = '\n';
            printString(buf,result);
        }
        return 1;
    }else if (strcmp(command[0],"cd")==0){//cd dir
        const char *dir = command[1];
        if (chdir(dir)>=0) {
            result[0] = '\2';
            //printString("",result);
        }else{
            *error = EXIT_FAILURE;
            printString("No Such Directory\n",result);
        }
        return 1;
    }
    return 0;
}
int outerCommand(char *command[],int fd[2],int *error){
   
    int err = execvp(command[0],command);// relative path, file, params
    if (err==-1) {
        *error = EXIT_FAILURE;
        printf("Run Command Error: %d\n",*error);
    }
    
    return 0;
}
#pragma mark- runProcess
int runProcess(char *command[],char *result){
    pid_t pid;
    int error = 0;
    
    int fd[2];
    pipe(fd);
    
    if (!innerCommand(command, result, &error)) { // if not listjobs
        pid = fork();
        if (pid <0) {
            printString("fork() error!",result);
            exit(EXIT_FAILURE);
        }
        int status;
        if (pid == 0) { //child process
            dup2(fd[1], 1); // redirect stdout
            outerCommand(command,fd,&error);
            exit(error);
        }else{//father process
            _latestPid = pid;
            while (waitpid(pid,&status,0)!=pid);
            
            close(fd[1]);
            read(fd[0], result, 1000);
            dup2(fd[0], 0);
        }
    }
    return error;
    
}
#pragma mark- makeCommand
void makeCommand(const char *buf,char *command[]){
    int wordIndex = 0;
    int letterIndex = 0;
    
    long length = strlen(buf);
    char word[kLength];
    bool isEnd = false;
    for (int i=0; i<length; i++) {
        char c = buf[i];//every letter
        if (c == ' ') {// make an word
            c = '\0';
        }else if (c == '\n'){//command end
            c = '\0';
            isEnd = true;
        }
        if (c == '&' && buf[i-1]==' '&&buf[i+1]=='\n') {
            c = '\0';
            command[wordIndex] = NULL;
            char *com = malloc(sizeof(char) * kLength);
            strncpy(com, buf,length-1);
            com[length-1] = '\0';
            return;
        }
        word[letterIndex] = c;
        letterIndex++;
        if (c == '\0') {
            char *copyWord = malloc(strlen(word)+1);// every word end
            strcpy(copyWord, word);
            command[wordIndex] = copyWord;
            
            memset(word,0,kLength);
            letterIndex = 0;
            wordIndex++;
            if (isEnd) { // command end
                command[wordIndex] = NULL;
                return ;
            }
        }
    }
}


#pragma mark- process
int process(char *buffer, char* result){
    char *command[kLength];
    makeCommand(buffer, command);

    return runProcess(command, result);

}



