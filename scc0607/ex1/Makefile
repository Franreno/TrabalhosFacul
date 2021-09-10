all: main.c functions.c ./IO/IO.c
	gcc -o main main.c functions.c ./IO/IO.c

run:
	make all
	./main

zip:
	zip -r 11954374.zip IO ex1.h functions.c main.c Makefile

clean:
	rm main
	rm *.zip