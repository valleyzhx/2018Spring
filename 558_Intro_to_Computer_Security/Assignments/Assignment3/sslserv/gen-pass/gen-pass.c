//
//  gen-pass.c
//  Assignment3
//
//  Created by Xiang on 2018/3/26.
//  Copyright © 2018年 Xiang. All rights reserved.
//
#include "gen-pass.h"

char* MD5_Encrypt(const char *data){
    MD5_CTX ctx;
    unsigned char md[16];
    char tmp[3] = {'0'};
    int i;
    
    MD5_Init(&ctx);
    MD5_Update(&ctx, data, strlen(data));
    MD5_Final(md, &ctx);
    
    char *md5_pass = malloc(1024*sizeof(char));
    memset(md5_pass, 0, 1024);
    for(i = 0; i < 16;i++)
    {
        sprintf(tmp, "%02X", md[i]);
        strcat(md5_pass, tmp);
    }
    return md5_pass;
}

bool savingUser(const char *userId, const char *password){
    
    if (checkExisting(userId)) {
        return false;
    }else{
        time_t ticks = time(NULL);
        char savedTime[100]={'\0'};
        snprintf(savedTime, sizeof(savedTime), "%.24s", ctime(&ticks));
        char saving[1000] = {'\0'};
        char *md5_pass = MD5_Encrypt(password);
        sprintf(saving, "%s,%s,%s\n", userId,md5_pass,savedTime);
        
        FILE *fptr = fopen("password.txt", "a+");
        fseek(fptr, 0, SEEK_END);
        fputs(saving,fptr);
        fclose(fptr);
        
        free(md5_pass);
    }
    return true;
}




bool checkExisting(const char *userId){
    FILE *fptr = fopen("password.txt", "r");
    fseek(fptr,0,SEEK_SET);
    bool exist = false;
    while(!feof(fptr)) {
        char savingStr[512] = {'\0'};
        fgets(savingStr, sizeof(savingStr), fptr);
        char *savedUserId = strtok(savingStr, ",");
        if (savedUserId!=NULL) {
            if (strcmp(userId,savedUserId)==0){
                exist = true;
                break;
            }
        }
    }
    fclose(fptr);
    
    return exist;
}
bool verifyUser(char *userId, char *password){
    char *md5_pass = MD5_Encrypt(password);
    FILE *fptr = fopen("password.txt", "r");
    fseek(fptr,0,SEEK_SET);
    bool verify = false;
    while(!feof(fptr)) {
        char savingStr[512] = {'\0'};
        fgets(savingStr, sizeof(savingStr), fptr);
        char *savedUserId = strtok(savingStr, ",");
        if (savedUserId!=NULL) {
            if (strcmp(userId,savedUserId)==0){
                char *savedPassword = strtok(NULL, ",");
                if (strcmp(md5_pass,savedPassword)==0) verify = true;
                break;
            }
        }
    }
    fclose(fptr);
    free(md5_pass);
    return verify;
}




