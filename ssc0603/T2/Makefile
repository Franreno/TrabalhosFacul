main.o: main.c
	gcc -c main.c -o main.o

ArvBin.o: ArvBin.c
	gcc -c ArvBin.c -o ArvBin.o

main: main.o ArvBin.o
	gcc -o main main.o ArvBin.o

all:
	make main

run: 
	make all
	./main

clean:
	rm *.o
	rm main