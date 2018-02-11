all:
	flex –l calc.l
	bison -dv calc.y
	gcc -o calc calc.tab.c lex.yy.c –lfl

test: prog.l prog.y
	flex –l prog.l # generate lex.yy.c
	bison -dv prog.y # generate
	# -ll for MacOS, -lfl for Ubuntu
	gcc calc.tab.c lex.yy.c -o calc –ll
