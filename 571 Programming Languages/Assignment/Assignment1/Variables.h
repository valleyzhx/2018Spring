//
//  Variables.h
//  testVariables
//
//  Created by Xiang on 2018/2/11.
//  Copyright © 2018年 Xiang. All rights reserved.
//

#ifndef Variables_h
#define Variables_h

#include <stdio.h>

typedef enum {
    VarTypeDefault = 0,
    VarTypeStart,
    VarTypeEnd,
} VarType;

typedef struct {
    char *name;
    float value;
    VarType type;
} Variable;

Variable newVariable(char *name, float value, VarType type);

void releaseVariables(void);

#endif /* Variables_h */
