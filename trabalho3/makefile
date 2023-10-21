all: cmdif entrada.txt
	./cmdif < entrada.txt

cmdif: lex.yy.c y.tab.c
	g++ -std=c++17 y.tab.c -o cmdif -ll	
	
lex.yy.c: cmdif.l
	lex cmdif.l
	
y.tab.c: cmdif.y
	yacc cmdif.y -Wcounterexamples
	
clean: 
	rm -f lex.yy.c y.tab.c cmdif