#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "Piece.h"
#include "Square.h"

class Board {
private:
    Piece* board[8][8];
    std::vector<Piece*> pieces[2];

public:
    Board();
    ~Board();

    void display() const;
    Piece* get_piece(Square s) const;
    void place_piece(Piece* p, Square s);
    void move(Square orig, Square dest);
    bool is_cell_empty(Square s) const;
    bool is_path_clear(Square orig, Square dest) const;
    
    std::string canonical_position() const;
    std::string pgn_piece_name(std::string const name, bool view_pawn, bool view_color) const;

    Square find_king(Color c) const;
    bool is_square_attacked(Square s, Color attackerColor) const;
    bool is_check(Color kingColor) const;

    void force_move(Square orig, Square dest, Piece*& captured);
    void undo_force_move(Square orig, Square dest, Piece* captured);

    bool has_legal_moves(Color c);
};

#endif
