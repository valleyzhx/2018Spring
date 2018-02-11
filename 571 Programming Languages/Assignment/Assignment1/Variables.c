//
//  Variables.c
//  testVariables
//
//  Created by Xiang on 2018/2/11.
//  Copyright © 2018年 Xiang. All rights reserved.
//

#include "Variables.h"
#include <string.h>

static Variable _varArray[100];
static int _varCount = 0;

Variable newVariable(char *name, float value, VarType type){
    Variable var = _varArray[_varCount];
    var.name = name;
    var.value = value;
    var.type = type;
    _varArray[_varCount++] = var;
    
    printf("newVar: %s\nvarCount:%d\n",name,_varCount);

    
    return var;
}

float getValueOfName(char *name){
    printf("getValueOfName: %s\nvarCount:%d\n",name,_varCount);
    for (int i=_varCount-1; i>=0; i--) {
        Variable var = _varArray[i];
        printf("name:%s\n",var.name);
        if(strcmp(var.name,name) == 0){
            var.name = name;
            return var.value;
        }
    }
    return 0.0;
}


Variable updateVariable(char *name, float value){
    Variable theVar;
    for (int i=_varCount-1; i>=0; i--) {
        Variable var = _varArray[i];
        if(strcmp(var.name,name) == 0){
            var.name = name;
            var.value = value;
            _varArray[i] = var;
            theVar = var;
            break;
        }
    }
    return theVar;
}

void releaseVariables(void){
    while (_varCount>0) {
        Variable var = _varArray[_varCount--];
        if(var.type == VarTypeStart){
            break;
        }
    }
}
