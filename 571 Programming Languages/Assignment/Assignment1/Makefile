EXP=1
all: calc

calc.tab.c calc.tab.h:	calc.y
	bison -d calc.y

lex.yy.c: calc.l calc.tab.h
	flex -l calc.l

calc: lex.yy.c calc.tab.c calc.tab.h
ifeq ($(shell uname), Darwin)
	gcc -o calc calc.tab.c lex.yy.c Variables.c -ll -std=c99;
else
	gcc -o calc calc.tab.c lex.yy.c Variables.c -lfl -std=c99;
endif
clean:
	rm calc calc.tab.c lex.yy.c calc.tab.h
run: calc
	./calc <testFiles/example${EXP}.prog

