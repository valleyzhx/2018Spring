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
#include <sys/types.h>
#include <sys/wait.h>


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
            //printString("",result);
        }else{
            *error = EXIT_FAILURE;
            char buf[kLength]={'\0'};
            sprintf(buf,"%s: does not exist\n",command[1]);
            printString(buf,result);
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
    
    if (!innerCommand(command, result, &error)) {
        pid = fork();
        if (pid <0) {
            printString("fork() error!",result);
            exit(EXIT_FAILURE);
        }
        int status;
        if (pid == 0) { //child process
            dup2(fd[1], 2); // redirect stderr
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
int makeCommand(const char *buf,char *command[]){
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
        }else if (c == '-'){
            return -1;
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
                return 0;
            }
        }
    }
    return -1;
}


#pragma mark- process
int process(char *buffer, char* result){
    char *command[kLength];
    int error = makeCommand(buffer, command);
    
    if (error == 0){
        bool pwd = strcmp(command[0],"pwd\0")==0;
        bool cd = strcmp(command[0],"cd\0")==0;
        bool ls = strcmp(command[0],"ls\0")==0;
        bool mkdir = strcmp(command[0],"mkdir\0")==0;
        bool rmdir = strcmp(command[0],"rmdir\0")==0;
        bool exit = strcmp(command[0],"exit\0")==0;
        
        if (pwd||cd||ls||mkdir||rmdir||exit) {
             return runProcess(command, result);
        }
    }
    strcpy(result, "invalid command!\n");
    return -1;

}



