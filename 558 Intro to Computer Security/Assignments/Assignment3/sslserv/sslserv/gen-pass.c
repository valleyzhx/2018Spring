//
//  gen-pass.c
//  Assignment3
//
//  Created by Xiang on 2018/3/26.
//  Copyright © 2018年 Xiang. All rights reserved.
//

#include "gen-pass.h"
#include <string.h>
#include <openssl/md5.h>

void MD5_Encrypt(char *data,char *result){
    MD5_CTX ctx;
    unsigned char md[16];
    char tmp[3] = {'0'};
    int i;
    
    MD5_Init(&ctx);
    MD5_Update(&ctx, data, strlen(data));
    MD5_Final(md, &ctx);
    
    for(i = 0; i < 16;i++)
    {
        sprintf(tmp, "%02X", md[i]);
        strcat(result, tmp);
    }
    //printf("%s\n", result);
}
