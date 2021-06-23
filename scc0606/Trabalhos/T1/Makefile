all: main

run: all
	./main

main: list.o main.o
	gcc -o main main.o list.o -lm

main.o: main.c sorting.h
	gcc -c main.c

list.o: list.c sorting.h
	gcc -c list.c

clean:
	rm *.o
	rm main
