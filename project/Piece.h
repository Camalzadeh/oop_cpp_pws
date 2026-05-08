#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <string>
#include "Square.h"

enum Color { White = 0, Black = 1 };

class Board;

class Piece {
protected:
    Color color;
    Square position;
    bool hasMoved;

public:
    Piece(Color pieceColor, Square initialPosition)
        : color(pieceColor), position(initialPosition), hasMoved(false) {}
    virtual ~Piece() {}

    Color getColor() const { return color; }
    Square getPosition() const { return position; }
    void setPosition(Square square, bool markMoved = true) {
        position = square;
        if (markMoved) {
            hasMoved = true;
        }
    }
    bool getHasMoved() const { return hasMoved; }
    void setHasMoved(bool moved) { hasMoved = moved; }

    virtual char pieceCode() const = 0;
    virtual std::string toString() const;
    virtual std::string displaySymbol() const;
    virtual void display() const { std::cout << toString(); }
    virtual bool isLegalMove(Square destination, const Board& board) const = 0;
};

class Rook : public Piece {
public:
    Rook(Color pieceColor, Square initialPosition) : Piece(pieceColor, initialPosition) {}
    char pieceCode() const override { return 'R'; }
    bool isLegalMove(Square destination, const Board& board) const override;
};

class Knight : public Piece {
public:
    Knight(Color pieceColor, Square initialPosition) : Piece(pieceColor, initialPosition) {}
    char pieceCode() const override { return 'N'; }
    bool isLegalMove(Square destination, const Board& board) const override;
};

class Bishop : public Piece {
public:
    Bishop(Color pieceColor, Square initialPosition) : Piece(pieceColor, initialPosition) {}
    char pieceCode() const override { return 'B'; }
    bool isLegalMove(Square destination, const Board& board) const override;
};

class Queen : public Piece {
public:
    Queen(Color pieceColor, Square initialPosition) : Piece(pieceColor, initialPosition) {}
    char pieceCode() const override { return 'Q'; }
    bool isLegalMove(Square destination, const Board& board) const override;
};

class King : public Piece {
public:
    King(Color pieceColor, Square initialPosition) : Piece(pieceColor, initialPosition) {}
    char pieceCode() const override { return 'K'; }
    bool isLegalMove(Square destination, const Board& board) const override;
};

class Pawn : public Piece {
public:
    Pawn(Color pieceColor, Square initialPosition) : Piece(pieceColor, initialPosition) {}
    char pieceCode() const override { return 'P'; }
    bool isLegalMove(Square destination, const Board& board) const override;
};

#endif
