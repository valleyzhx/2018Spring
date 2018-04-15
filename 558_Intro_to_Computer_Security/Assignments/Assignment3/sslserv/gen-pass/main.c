//
//  main.c
//  gen-pass
//
//  Created by Xiang on 2018/3/27.
//  Copyright © 2018年 Xiang. All rights reserved.
//

#include <stdio.h>
#include "gen-pass.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    bool goon = true;
    
    while (goon) {
        printf("create the UserID:\n");
        char userID[100] = {'\0'};
        scanf("%s",userID);
        if (checkExisting(userID)) {
            printf("the ID already exists\n");
        }else{
            printf("create the password:\n");
            char password[100] = {'\0'};
            scanf("%s",password);
            if (savingUser(userID, password)) {
                printf("Saving Done!\n");
            }
        }
        printf("Do you want to create more users?[Y/N(default)]\n");
        char c[10] = {'\0'};
        scanf("%s",c);
        if (c[0] == 'Y'||c[0] == 'y') {
            goon = true;
        }else{
            goon = false;
        }
    }
    
    
    return 0;
}
