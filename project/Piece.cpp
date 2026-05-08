#include "Piece.h"
#include "Board.h"
#include <cmath>

bool Rook::is_legal_move(Square dest, const Board& board) const {
    int dr = dest.getRow() - pos.getRow();
    int dc = dest.getCol() - pos.getCol();
    if (dr == 0 || dc == 0) {
        return board.is_path_clear(pos, dest);
    }
    return false;
}

bool Knight::is_legal_move(Square dest, const Board& board) const {
    int dr = std::abs(dest.getRow() - pos.getRow());
    int dc = std::abs(dest.getCol() - pos.getCol());
    return (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
}

bool Bishop::is_legal_move(Square dest, const Board& board) const {
    int dr = std::abs(dest.getRow() - pos.getRow());
    int dc = std::abs(dest.getCol() - pos.getCol());
    if (dr == dc) {
        return board.is_path_clear(pos, dest);
    }
    return false;
}

bool Queen::is_legal_move(Square dest, const Board& board) const {
    int dr = std::abs(dest.getRow() - pos.getRow());
    int dc = std::abs(dest.getCol() - pos.getCol());
    if (dr == dc || dest.getRow() == pos.getRow() || dest.getCol() == pos.getCol()) {
        return board.is_path_clear(pos, dest);
    }
    return false;
}

bool King::is_legal_move(Square dest, const Board& board) const {
    int dr = std::abs(dest.getRow() - pos.getRow());
    int dc = std::abs(dest.getCol() - pos.getCol());
    
    // Prevent moving to the same square
    if (dr == 0 && dc == 0) return false;
    
    // Normal king move: 1 square in any direction
    if (dr <= 1 && dc <= 1) {
        return true;
    }
    
    // Castling: King moves 2 squares horizontally on the same rank
    if (dr == 0 && dc == 2 && !hasMoved) {
        int rook_col = (dest.getCol() > pos.getCol()) ? 7 : 0;  // King-side or Queen-side
        Square rook_pos(pos.getRow(), rook_col);
        Piece* rook = board.get_piece(rook_pos);
        
        // Check if rook exists, hasn't moved, same color, and path is clear
        if (rook && rook->getColor() == color && !rook->getHasMoved() && 
            board.is_path_clear(pos, rook_pos)) {
            // Additional check: verify it's a rook
            std::string rook_name = board.pgn_piece_name(rook->to_string(), false, false);
            if (rook_name == "R") {
                return true;
            }
        }
    }
    
    return false;
}

bool Pawn::is_legal_move(Square dest, const Board& board) const {
    int r0 = pos.getRow();
    int c0 = pos.getCol();
    int r1 = dest.getRow();
    int c1 = dest.getCol();
    int direction = (color == White) ? 1 : -1;
    int startRow = (color == White) ? 1 : 6;

    if (c0 == c1) {
        if (r1 == r0 + direction) {
            return board.is_cell_empty(dest);
        }
        if (r0 == startRow && r1 == r0 + 2 * direction) {
            return board.is_cell_empty(dest) && board.is_cell_empty(Square(r0 + direction, c0));
        }
    }
    else if (std::abs(c1 - c0) == 1 && r1 == r0 + direction) {
        Piece* p = board.get_piece(dest);
        // Normal capture: enemy piece on destination
        if (p != nullptr && p->getColor() != color) {
            return true;
        }
        // En passant capture: destination is empty but matches en passant square
        if (board.is_cell_empty(dest) && dest == board.get_en_passant_square()) {
            return true;
        }
    }

    return false;
}
