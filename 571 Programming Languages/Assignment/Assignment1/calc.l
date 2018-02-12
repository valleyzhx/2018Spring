%{
#include <stdio.h>
#include "Variables.h"
#include "calc.tab.h"
int num_lines = 0;
%}

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

"+"	{	return(TOK_ADD);	}
"-"	{	return(TOK_SUB);	}
"*"	{	return(TOK_MUL);	}
"/"	{	return(TOK_DIV);	}

[a-z][a-zA-Z0-9]* {
    yylval.string_val = strdup(yytext);
    return(TOK_ID);}

[ \n] num_lines++;
. {printf("Invalid character '%c', ignored\n",
			yytext[0]);
	}

%%

