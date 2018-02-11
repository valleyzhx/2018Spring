%{
#include <stdio.h>
#include "calc.tab.h"
%}

digit	([0-9])

%%

"main()"        { return(TOK_MAIN); }
"println"       {   return(TOK_PRINTLN);  }

{digit}+\.{digit}+ {
    scanf(yytext, "%f", &(yylval.float_val));
    return TOK_FLOAT;
}

{digit}+	{
    sscanf(yytext, "%d", &(yylval.int_val));
    return TOK_NUM;
}

";"	{	return(TOK_SEMICOLON);	}
"+"	{	return(TOK_ADD);	}
"-"	{	return(TOK_SUB);	}
"*"	{	return(TOK_MUL);	}
"/"	{	return(TOK_DIV);	}

[ \t] /* eat up the white space */
\n  { // yylineno is build in flex }

. { /* catch up all pattern */
    printf("Invalid character '%c', ignored\n",
            yytext[0]);
}

%%
