all: ass

ass: lex.yy.c ass.tab.c ass.tab.h main.o
	gcc -o ass ass.tab.c lex.yy.c main.o -DYYDEBUG=1

ass.tab.c ass.tab.h:	ass.y
	bison -t -v -d ass.y

lex.yy.c: ass.l ass.tab.h
	flex ass.l

main.o: main.h main.c
	gcc -c main.c


clean:
	rm ass ass.tab.c lex.yy.c ass.tab.h main.o
