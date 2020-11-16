lde.o: lde.c
	gcc -c lde.c -o lde.o

option.o: option.c
	gcc -c option.c -o option.o

main.o: main.c
	gcc -c main.c -o main.o

all: main.o lde.o option.o 
	gcc -o main main.o lde.o option.o

run:
	make all
	./main

clean:
	rm *.o
	rm main
