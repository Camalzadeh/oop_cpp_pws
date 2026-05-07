CC=g++
CFLAGS=-Wall -std=c++11

all: chess

chess: main.o Game.o Board.o Piece.o
	$(CC) $(CFLAGS) -o chess main.o Game.o Board.o Piece.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Game.o: Game.cpp Game.h
	$(CC) $(CFLAGS) -c Game.cpp

Board.o: Board.cpp Board.h
	$(CC) $(CFLAGS) -c Board.cpp

Piece.o: Piece.cpp Piece.h
	$(CC) $(CFLAGS) -c Piece.cpp

clean:
	rm -f *.o chess
