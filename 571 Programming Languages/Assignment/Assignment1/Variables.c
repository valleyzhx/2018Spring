//
//  Variables.c
//  testVariables
//
//  Created by Xiang on 2018/2/11.
//  Copyright © 2018年 Xiang. All rights reserved.
//

#include "Variables.h"
#include <string.h>
#include <stdlib.h>

static Variable _varArray[100];
static int _varCount = 0;

void printVariables(void){
//    for(int i=0;i<_varCount;i++){
//        Variable var = _varArray[i];
//        printf("{%s,%.2f} ",var.name,var.value);
//    }
//    printf("\n");
}



Variable newVariable(char *name, float value, VarType type){
    //printf("new : %s",name);
    Variable var = _varArray[_varCount];
    char *buffer = malloc(10*sizeof(char));
    strcpy(buffer,name);
    var.name = buffer;
    var.value = value;
    var.type = type;
    _varArray[_varCount] = var;
    _varCount++;
    //printf("new: %s = %f count:%d\n",name,value,_varCount);
    printVariables();
    
    return var;
}

float getValueOfName(char *name){
    for (int i=_varCount-1; i>=0; i--) {
        Variable var = _varArray[i];
        
        if(strcmp(var.name,name) == 0){
            //printf("get:%s = %f\n",var.name,var.value);
            return var.value;
        }
    }
    return 0.0;
}


Variable updateVariable(char *name, float value){
    Variable theVar;
    //printf("looking for => %s\n",name);
    for (int i=_varCount-1; i>=0; i--) {
        Variable var = _varArray[i];
        if(strcmp(var.name,name) == 0){
            var.value = value;
            //printf("update:%s = %f\n",var.name,var.value);

            _varArray[i] = var;
            theVar = var;
            break;
        }
    }
    printVariables();

    return theVar;
}

void releaseVariables(void){
    while (_varCount>=0) {
        Variable var = _varArray[_varCount-1];
        _varCount--;
        if(var.type == VarTypeStart){
            break;
        }
    }
    printVariables();

}
