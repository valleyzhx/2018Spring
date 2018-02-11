//
//  Variables.c
//  testVariables
//
//  Created by Xiang on 2018/2/11.
//  Copyright © 2018年 Xiang. All rights reserved.
//

#include "Variables.h"

static Variable _varArray[100];
static int _varCount = 0;

Variable newVariable(char *name, float value, VarType type){
    Variable var = _varArray[_varCount++];
    var.name = name;
    var.value = value;
    var.type = type;
    return var;
}

void releaseVariables(void){
    while (_varCount>0) {
        Variable var = _varArray[_varCount--];
        if(var.type == VarTypeStart){
            break;
        }
    }
}

void yyerror(char *s, ...) {
    va_list ap;
    va_start(ap, s);

    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

int main()
{
    // printf("> ");
    return yyparse();
}
