%{
#include <stdio.h>
#include "Variables.h"
#include "calc.tab.h"
void print_error(const char *msg);
%}

%option yylineno

digit	([0-9])

%%

"print"       {       return(TOK_PRINT);}
"float"         {    return(TOK_FLOAT);}

{digit}+\.{digit}+	{
		sscanf(yytext, "%f", &(yylval.float_val));
		return TOK_NUM;
		}
"main()" {return(TOK_MAIN);}

"{" { newVariable("start",0.0,VarTypeStart); return(TOK_START);}
"}" { releaseVariables(); return(TOK_END);}
";"	{	return(TOK_SEMICOLON);	}
"(" {    return(TOK_PAREN_START);    }
")" {    return(TOK_PAREN_END);    }

"=" {   return(TOK_EQUAL);  }

"-"	{	return(TOK_SUB);	}
"*"	{	return(TOK_MUL);	}

\s {}

[a-z][a-zA-Z0-9]* {
    yylval.string_val = strdup(yytext);
    return(TOK_ID);}

[a-zA-Z0-9]+ {
    char buf[30];
    sprintf(buf,"Lexical analysis error: %s",yytext);
    print_error(buf);
}
[ \n]
. { char buf[30];
    sprintf(buf,"Lexical analysis error: %s",yytext);
    print_error(buf);
}
%%
void print_error(const char *msg) {
    printf("%s, line %d\n",msg,yylineno);
    //exit(0);
}

