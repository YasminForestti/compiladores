all: saida codigo
	echo "=== Execução ==="
	./interpretador < codigo

codigo: saida entrada.txt
	./saida < entrada.txt > codigo
	echo "=== Codigo ==="
	cat codigo

saida: lex.yy.c y.tab.c
	g++ y.tab.c -o saida -lfl

lex.yy.c: cmdif.l
	lex cmdif.l
	
y.tab.c: teste.y
	yacc teste.y 
	
clean: 
	rm -f lex.yy.c y.tab.c cmdif