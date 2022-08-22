CC=gcc
CFLAGS=-std=c99 -Wall -g
LDFLAGS=
SRC=./src/
INC=-I./include
OBJ=Listes.o ATR.o
LEVENSHTEIN=Levenshtein.o
ARBREBK=ArbreBK.o
V1=correcteur_0.o
V2=correcteur_1.o
V3=correcteur_2.o

all: correcteur_0 correcteur_1 correcteur_2

correcteur_0: $(OBJ) $(V1)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

correcteur_1: $(OBJ) $(V2) $(LEVENSHTEIN)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

correcteur_2: $(OBJ) $(V3) $(LEVENSHTEIN) $(ARBREBK)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

%.o: $(SRC)%.c
	$(CC) $(INC) -c $< $(CFLAGS) $(LDFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f correcteur_1
	rm -f correcteur_0
	rm -f correcteur_2
	rm -f ArbreBK.dot
	rm -f ArbreBK.pdf