COMP = gcc
SRC = ./src
INC = -I ./headers
FLAGS = -Wall -g
OUT = programaTrab

OBJECTS = funcoesFornecidas.o functions.o registro.o binary.o utils.o parser.o list.o

all: $(OBJECTS)
	$(COMP) $(SRC)/main.c $(OBJECTS) -o $(OUT) $(INC) $(FLAGS)

%.o: $(SRC)/%.c
	$(COMP) -c $< $(INC) $(FLAGS) -o $@

run:
	./$(OUT)

clean:
	rm -f *.o *.bin *.zip
	find . -type f -executable -exec rm '{}' \;

zip:
	zip -r trabZip.zip Makefile ./src ./headers
