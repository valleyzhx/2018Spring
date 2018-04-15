//
//  gen-pass.h
//  Assignment3
//
//  Created by Xiang on 2018/3/26.
//  Copyright © 2018年 Xiang. All rights reserved.
//

#ifndef gen_pass_h
#define gen_pass_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
#include <time.h>

char* MD5_Encrypt(const char *data);

bool savingUser(const char *userId, const char *password);
bool checkExisting(const char *userId);
bool verifyUser(char *userId, char *password);



#endif /* gen_pass_h */
