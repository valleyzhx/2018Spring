%{
#include <stdio.h>
%}

%token TOK_SEMICOLON TOK_ADD TOK_SUB TOK_MUL TOK_DIV TOK_NUM TOK_PRINTLN TOK_FLOAT

%union{
        int int_val;
	float float_val;
}

/*
%type <int_val> expr TOK_NUM
%type <float_val> expr_float TOK_FLOAT
*/

%type <int_val> TOK_NUM
%type <float_val> TOK_FLOAT

%left TOK_ADD TOK_SUB
%left TOK_MUL TOK_DIV

%%

stmt: /* could be empty */
 | stmt expr_stmt /* which means could be a lot of expr_stmt */
;

expr_stmt: expr TOK_SEMICOLON   /* do nothing */
 | expr_float TOK_SEMICOLON     /* do nothing */
 | TOK_PRINTLN expr TOK_SEMICOLON
		{
			fprintf(stdout, "the value is %d\n", $2);
		}
 | TOK_PRINTLN expr_float TOK_SEMICOLON
		{ fprintf(stdout, "the value is %f\n", $2);}
;

expr_float: TOK_FLOAT               {$$ = $1;}
| expr_float TOK_ADD expr           {$$ = $1 + $3;}
| expr TOK_ADD expr_float           {$$ = $1 + $3;}
| expr_float TOK_ADD expr_float     {$$ = $1 + $3;}

| expr_float TOK_SUB expr           {$$ = $1 - $3;}
| expr TOK_SUB expr_float           {$$ = $1 - $3;}
| expr_float TOK_SUB expr_float     {$$ = $1 - $3;}

| expr_float TOK_MUL expr           {$$ = $1 * $3;}
| expr TOK_MUL expr_float           {$$ = $1 * $3;}
| expr_float TOK_MUL expr_float     {$$ = $1 * $3;}

| expr_float TOK_DIV expr           {$$ = $1 * 1.0 / $3;}
| expr TOK_DIV expr_float           {$$ = $1 * 1.0 / $3;}
| expr_float TOK_DIV expr_float     {$$ = $1 * 1.0 / $3;}

;

expr: TOK_NUM { $$=$1; }
 |	expr TOK_ADD expr
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
		$$ = $1 / $3;
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
