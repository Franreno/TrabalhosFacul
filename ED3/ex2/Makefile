COMP = gcc
SRC = ./src
INC = -I ./headers
FLAGS = -Wall -Werror
OUT = prog

OBJECTS = pessoa.o funcoesFornecidas.o

all: $(OBJECTS)
	$(COMP) $(SRC)/main.c $(OBJECTS) -o $(OUT) $(INC) $(FLAGS)

%.o: $(SRC)/%.c
	$(COMP) -c $< $(INC) $(FLAGS) -o $@

run:
	./$(OUT)

clean:
	rm -f *.o

zip:
	zip -r 11954374.zip Makefile ./src ./headers