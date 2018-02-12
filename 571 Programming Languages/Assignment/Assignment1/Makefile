# flex generate lex.yy.c
#
# bison generate prog.tab.c prog.tab.h prog.output, which could be helpful
# -ll for MacOS, -lfl for Ubuntu

all:
	flex –l calc.l
	bison -dv calc.y
	gcc -o calc calc.tab.c lex.yy.c –lfl

test: prog.l prog.y Variables.c Variables.h
	flex -l prog.l
	bison -dv prog.y
	gcc Variables.c prog.tab.c lex.yy.c -o $@ -ll

clean:
	rm *.tab.c *.tab.h *.yy.c *.output test prog
