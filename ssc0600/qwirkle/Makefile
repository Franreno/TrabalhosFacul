Symbols.o: Symbols.c
	gcc -c Symbols.c -o Symbols.o

Paineis.o: Paineis.c
	gcc -c Paineis.c -o Paineis.o

matrix_print.o: matrix_print.c
	gcc -c matrix_print.c -o matrix_print.o

jogada.o: jogada.c
	gcc -c jogada.c -o jogada.o

distribuicao.o: distribuicao.c
	gcc -c distribuicao.c -o distribuicao.o

rules.o: rules.c
	gcc -c rules.c -o rules.o

pontuacao.o: pontuacao.c
	gcc -c pontuacao.c -o pontuacao.o

main.o: main.c
	gcc -c main.c -o main.o

all: main.o Symbols.o Paineis.o matrix_print.o jogada.o distribuicao.o rules.o pontuacao.o 
	gcc -o main main.o Symbols.o Paineis.o matrix_print.o jogada.o distribuicao.o rules.o pontuacao.o


test.o: test.c
	gcc -c test.c -o test.o

teste: test.o Paineis.o
	gcc -o teste test.o Paineis.o

runteste:
	make teste
	./teste



run:
	make all
	./main

clean:
	rm *.o
	rm main
