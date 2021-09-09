all: main.c functions.c ./IO/IO.c
	gcc -o main main.c functions.c ./IO/IO.c


run:
	make all
	./main

zip:
	zip -r 11954374.zip IO ex1.h functions.c main.c Makefile

testes: all
	make all
	./main < testes/1.in
	./main < testes/2.in
	./main < testes/3.in
	./main < testes/4.in
	./main < testes/5.in
	./main < testes/6.in
	./main < testes/7.in

clean:
	rm main
	rm *.zip