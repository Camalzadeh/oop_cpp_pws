CC=g++
CFLAGS=-Wall -std=c++11

all: chess

chess: main.o Jeu.o Echiquier.o Piece.o
	$(CC) $(CFLAGS) -o chess main.o Jeu.o Echiquier.o Piece.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Jeu.o: Jeu.cpp Jeu.h
	$(CC) $(CFLAGS) -c Jeu.cpp

Echiquier.o: Echiquier.cpp Echiquier.h
	$(CC) $(CFLAGS) -c Echiquier.cpp

Piece.o: Piece.cpp Piece.h
	$(CC) $(CFLAGS) -c Piece.cpp

clean:
	rm -f *.o chess
