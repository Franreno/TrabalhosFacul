main.o: main.c
	gcc -c main.c -o main.o

avl.o: avl.c
	gcc -c avl.c -o avl.o

all: main.o avl.o
	gcc -o main main.o avl.o

run:
	make all
	./main

clean:
	rm *.o
	rm main