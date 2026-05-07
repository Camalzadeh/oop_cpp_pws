#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <iostream>
#include "Square.h"

enum Color { White = 0, Black = 1 };

class Board;

class Piece {
protected:
    Color color;
    std::string name;
    Square pos;
    bool hasMoved;

public:
    Piece(Color c, std::string n, Square s) : color(c), name(n), pos(s), hasMoved(false) {}
    virtual ~Piece() {}

    Color getColor() const { return color; }
    Square getPos() const { return pos; }
    void setPos(Square s) { pos = s; hasMoved = true; }
    bool getHasMoved() const { return hasMoved; }
    std::string to_string() const { return name; }

    virtual void display() const { std::cout << name; }
    virtual bool is_legal_move(Square dest, const Board& board) const = 0;
};

class Rook : public Piece {
public:
    Rook(Color c, std::string n, Square s) : Piece(c, n, s) {}
    bool is_legal_move(Square dest, const Board& board) const override;
};

class Knight : public Piece {
public:
    Knight(Color c, std::string n, Square s) : Piece(c, n, s) {}
    bool is_legal_move(Square dest, const Board& board) const override;
};

class Bishop : public Piece {
public:
    Bishop(Color c, std::string n, Square s) : Piece(c, n, s) {}
    bool is_legal_move(Square dest, const Board& board) const override;
};

class Queen : public Piece {
public:
    Queen(Color c, std::string n, Square s) : Piece(c, n, s) {}
    bool is_legal_move(Square dest, const Board& board) const override;
};

class King : public Piece {
public:
    King(Color c, std::string n, Square s) : Piece(c, n, s) {}
    bool is_legal_move(Square dest, const Board& board) const override;
};

class Pawn : public Piece {
public:
    Pawn(Color c, std::string n, Square s) : Piece(c, n, s) {}
    bool is_legal_move(Square dest, const Board& board) const override;
};

#endif
