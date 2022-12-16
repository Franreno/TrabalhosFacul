users.o: users.c
	gcc -o users.o -c users.c

paineis.o: paineis.c
	gcc -o paineis.o -c paineis.c

user_interface.o: user_interface.c
	gcc -o user_interface.o -c user_interface.c

adm_interface.o: adm_interface.c
	gcc -o adm_interface.o -c adm_interface.c

main.o: main.c
	gcc -o main.o -c main.c

main: main.o paineis.o users.o user_interface.o adm_interface.o
	gcc -o main main.c paineis.o users.o user_interface.o adm_interface.o

all: main

run:
	make all
	./main

clean:
	rm *.o main
