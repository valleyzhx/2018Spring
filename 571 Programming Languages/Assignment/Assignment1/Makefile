all:
	flex –l calc.l
	bison -dv calc.y
	gcc -o calc calc.tab.c lex.yy.c –lfl

test: prog.l prog.y Variables.c Variables.h
	# generate lex.yy.c
	# -l, --lex-compat        maximal compatibility with original lex
	flex -l prog.l
	# generate prog.tab.c prog.tab.h prog.output, which could be helpful
	bison -dv prog.y
	# -ll for MacOS, -lfl for Ubuntu
	gcc Variables.c prog.tab.c lex.yy.c -o prog -ll

clean:
	rm *.tab.c *.tab.h *.yy.c *.output
