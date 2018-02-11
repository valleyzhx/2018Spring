%{
#include <stdio.h>
#include "Variables.h"

%}

%token TOK_SEMICOLON TOK_ADD TOK_SUB TOK_MUL TOK_DIV TOK_NUM TOK_PRINT
 token TOK_START TOK_END TOK_MAIN TOK_FLOAT TOK_ID TOK_EQUAL
       TOK_PAREN_START TOK_PAREN_END
%union{
        Variable var_val;
}

/*%type <int_val> expr TOK_NUM*/
%type <float_val> expr TOK_NUM

%left TOK_ADD TOK_SUB
%left TOK_MUL TOK_DIV

%%

prog:
    |TOK_MAIN TOK_START stmts TOK_END
;
stmts:
    | stmt TOK_SEMICOLON stmts
;
stmt:
    | TOK_FLOAT TOK_ID { newVariable("new",0);}
    | TOK_ID TOK_EQUAL expr
    | TOK_PRINT TOK_ID  {fprintf(stdout, "the value is %f\n", $2);}
    | TOK_START stmts TOK_END
;

expr:
    |TOK_ID { $$ = $1; }
    |TOK_PAREN_START TOK_DIV TOK_ID TOK_PAREN_END {$$ = -$1; }
    |TOK_NUM { $$ = $1; }
	|expr TOK_ADD expr
	  {
		$$ = $1 + $3;
	  }
	| expr TOK_SUB expr
	  {
		$$ = $1 - $3;
	  }
	| expr TOK_MUL expr
	  {
		$$ = $1 * $3;
	  }
	| expr TOK_DIV expr
	  {
		$$ = $1 * 1.0/ $3;
	  }

;


%%

int yyerror(char *s)
{
	printf("syntax error\n");
	return 0;
}

int main()
{
   yyparse();
   return 0;
}
