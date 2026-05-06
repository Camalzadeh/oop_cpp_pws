#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <iostream>
#include "Square.h"

enum Color { White = 0, Black = 1 };

class Echiquier;

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

    virtual void affiche() const { std::cout << name; }
    virtual bool is_legal_move(Square dest, const Echiquier& board) const = 0;
};

class Tour : public Piece {
public:
    Tour(Color c, std::string n, Square s) : Piece(c, n, s) {}
    bool is_legal_move(Square dest, const Echiquier& board) const override;
};

class Cavalier : public Piece {
public:
    Cavalier(Color c, std::string n, Square s) : Piece(c, n, s) {}
    bool is_legal_move(Square dest, const Echiquier& board) const override;
};

class Fou : public Piece {
public:
    Fou(Color c, std::string n, Square s) : Piece(c, n, s) {}
    bool is_legal_move(Square dest, const Echiquier& board) const override;
};

class Dame : public Piece {
public:
    Dame(Color c, std::string n, Square s) : Piece(c, n, s) {}
    bool is_legal_move(Square dest, const Echiquier& board) const override;
};

class Roi : public Piece {
public:
    Roi(Color c, std::string n, Square s) : Piece(c, n, s) {}
    bool is_legal_move(Square dest, const Echiquier& board) const override;
};

class Pion : public Piece {
public:
    Pion(Color c, std::string n, Square s) : Piece(c, n, s) {}
    bool is_legal_move(Square dest, const Echiquier& board) const override;
};

#endif
