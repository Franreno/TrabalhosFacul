#-----------------Ex 1a----------------------
exercicio1a: exercicio1a.c
	gcc -o exercicio1a exercicio1a.c -lm
#-------------------------------------------

#-----------------Ex 1b----------------------
exercicio1b: exercicio1b.c
	gcc -o exercicio1b exercicio1b.c -lm
#-------------------------------------------

#-----------------Ex 1c----------------------
exercicio1c: exercicio1c.c
	gcc -o exercicio1c exercicio1c.c -lm
#-------------------------------------------

#-----------------Ex 1d----------------------
exercicio1d: exercicio1d.c
	gcc -o exercicio1d exercicio1d.c -lm
#-------------------------------------------

#-----------------Ex 2a----------------------
exercicio2a: exercicio2a.c
	gcc -o exercicio2a exercicio2a.c -lm
#-------------------------------------------

#-----------------Ex 2b----------------------
exercicio2b: exercicio2b.c
	gcc -o exercicio2b exercicio2b.c -lm
#-------------------------------------------

#-----------------Ex 2c----------------------
exercicio2c: exercicio2c.c
	gcc -o exercicio2c exercicio2c.c -lm
#-------------------------------------------

#-----------------CLEAN(linux)---------------
clean:
	find . -type f -executable -exec rm '{}' \;
#-------------------------------------------

all: exercicio1a exercicio1b exercicio1c exercicio1d exercicio2a exercicio2b exercicio2c

run: all
	./exercicio1a
	./exercicio1b
	./exercicio1c
	./exercicio1d
	./exercicio2a
	./exercicio2b
	./exercicio2c