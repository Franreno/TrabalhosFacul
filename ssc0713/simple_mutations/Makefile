all: mutations.c
	gcc -o mutations mutations.c -march=native -O3

run:
	make all
	./mutations > res.txt

clean: 
	find . -type f -executable -exec rm '{}' \;