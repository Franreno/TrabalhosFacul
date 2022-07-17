COMP = g++
SRC = ./src
INC = -I ./headers
FLAGS = -Wall -g
OUT = programaTrab

OBJECTS = Graph.o binary.o utils.o funcoesFornecidas.o algmachine.o

all: $(OBJECTS)
	$(COMP) $(SRC)/main.cpp $(OBJECTS) -o $(OUT) $(INC) $(FLAGS)

%.o: $(SRC)/%.cpp
	$(COMP) -c $< $(INC) $(FLAGS) -o $@

run:
	./$(OUT)

clean:
	rm -f *.o *.bin *.zip
	find . -type f -executable -exec rm '{}' \;

zip:
	zip -r trabZip.zip Makefile ./src ./headers