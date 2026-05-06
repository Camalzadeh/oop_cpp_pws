#include "Piece.h"
#include "Echiquier.h"
#include <cmath>

bool Tour::is_legal_move(Square dest, const Echiquier& board) const {
    int dr = dest.getRow() - pos.getRow();
    int dc = dest.getCol() - pos.getCol();
    if (dr == 0 || dc == 0) {
        return board.is_path_clear(pos, dest);
    }
    return false;
}

bool Cavalier::is_legal_move(Square dest, const Echiquier& board) const {
    int dr = std::abs(dest.getRow() - pos.getRow());
    int dc = std::abs(dest.getCol() - pos.getCol());
    return (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
}

bool Fou::is_legal_move(Square dest, const Echiquier& board) const {
    int dr = std::abs(dest.getRow() - pos.getRow());
    int dc = std::abs(dest.getCol() - pos.getCol());
    if (dr == dc) {
        return board.is_path_clear(pos, dest);
    }
    return false;
}

bool Dame::is_legal_move(Square dest, const Echiquier& board) const {
    int dr = std::abs(dest.getRow() - pos.getRow());
    int dc = std::abs(dest.getCol() - pos.getCol());
    if (dr == dc || dest.getRow() == pos.getRow() || dest.getCol() == pos.getCol()) {
        return board.is_path_clear(pos, dest);
    }
    return false;
}

bool Roi::is_legal_move(Square dest, const Echiquier& board) const {
    int dr = std::abs(dest.getRow() - pos.getRow());
    int dc = std::abs(dest.getCol() - pos.getCol());
    return (dr <= 1 && dc <= 1);
}

bool Pion::is_legal_move(Square dest, const Echiquier& board) const {
    int r0 = pos.getRow();
    int c0 = pos.getCol();
    int r1 = dest.getRow();
    int c1 = dest.getCol();
    int direction = (color == White) ? 1 : -1;
    int startRow = (color == White) ? 1 : 6;

    // Simple move
    if (c0 == c1) {
        if (r1 == r0 + direction) {
            return board.est_case_vide(dest);
        }
        if (r0 == startRow && r1 == r0 + 2 * direction) {
            return board.est_case_vide(dest) && board.est_case_vide(Square(r0 + direction, c0));
        }
    }
    // Capture
    else if (std::abs(c1 - c0) == 1 && r1 == r0 + direction) {
        Piece* p = board.get_piece(dest);
        return (p != nullptr && p->getColor() != color);
    }

    return false;
}
