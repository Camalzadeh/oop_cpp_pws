#include "Game.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Game::Game() : turn(White), result("?-?"), game_over(false), turn_count(1) {}

void Game::display() const {
    board.display();
}

void Game::move(string orig_str, string dest_str, char promotion_choice) {
    Square orig(orig_str);
    Square dest(dest_str);

    if (!orig.isValid() || !dest.isValid()) {
        cout << "Invalid coordinates." << endl;
        return;
    }

    Piece* p = board.get_piece(orig);
    if (!p) {
        cout << "No piece at origin." << endl;
        return;
    }

    if (p->getColor() != turn) {
        cout << "It's not your turn." << endl;
        return;
    }
    
    // Prevent moving to the same square
    if (orig == dest) {
        cout << "Destination must be different from origin." << endl;
        return;
    }

    if (!p->is_legal_move(dest, board)) {
        cout << "Illegal move geometry or obstacles." << endl;
        return;
    }

    Piece* target = board.get_piece(dest);
    if (target && target->getColor() == turn) {
        cout << "Cannot capture your own piece." << endl;
        return;
    }

    bool moved_piece_is_pawn = (board.pgn_piece_name(p->to_string(), true, false) == "P");

    Piece* captured = nullptr;
    Piece* rook_captured = nullptr;
    Piece* en_passant_victim = nullptr;
    Square rook_orig, rook_dest;
    bool king_moved_before = false;
    bool rook_moved_before = false;
    bool is_castling = false;
    bool is_en_passant = false;

    // Check if this is a castling move
    if (board.pgn_piece_name(p->to_string(), false, false) == "K" && 
        orig.getRow() == dest.getRow() && 
        abs(dest.getCol() - orig.getCol()) == 2) {
        is_castling = true;
        int rook_col_orig = (dest.getCol() > orig.getCol()) ? 7 : 0;
        int rook_col_dest = (dest.getCol() > orig.getCol()) ? 5 : 3;
        rook_orig = Square(orig.getRow(), rook_col_orig);
        rook_dest = Square(orig.getRow(), rook_col_dest);
        
        // Castling validation: king cannot be in check or pass through check
        if (board.is_check(turn)) {
            cout << "Cannot castle: King is in check." << endl;
            return;
        }
        
        // Check if king passes through check
        int min_col = std::min(orig.getCol(), dest.getCol());
        int max_col = std::max(orig.getCol(), dest.getCol());
        for (int c = min_col; c <= max_col; c++) {
            if (board.is_square_attacked(Square(orig.getRow(), c), turn == White ? Black : White)) {
                cout << "Cannot castle: King passes through check." << endl;
                return;
            }
        }
    }
    
    // Check if this is an en passant capture
    if (moved_piece_is_pawn &&
        abs(dest.getCol() - orig.getCol()) == 1 && 
        dest == board.get_en_passant_square()) {
        is_en_passant = true;
        // The captured pawn is on the same row as origin, same column as destination
        Square victim_square(orig.getRow(), dest.getCol());
        en_passant_victim = board.get_piece(victim_square);
    }

    board.force_move(orig, dest, captured, king_moved_before);
    
    // If en passant, also remove the captured pawn
    if (is_en_passant && en_passant_victim) {
        Square victim_square(orig.getRow(), dest.getCol());
        // record and remove the victim pawn
        board.record_capture(en_passant_victim, p->getColor());
        board.remove_piece(victim_square);
    }
    
    // If castling, also move the rook
    if (is_castling) {
        board.force_move(rook_orig, rook_dest, rook_captured, rook_moved_before);
    }
    
    if (board.is_check(turn)) {
        board.undo_force_move(orig, dest, captured, king_moved_before);
        if (is_castling) {
            board.undo_force_move(rook_orig, rook_dest, rook_captured, rook_moved_before);
        }
        // Restore en passant victim if necessary
        if (is_en_passant && en_passant_victim) {
            Square victim_square(orig.getRow(), dest.getCol());
            board.restore_piece(en_passant_victim, victim_square);
        }
        cout << "Move leaves king in check." << endl;
        return;
    }

    Color opponent = (turn == White ? Black : White);
    
    if (moved_piece_is_pawn) {
        if (dest.getRow() == (p->getColor() == White ? 7 : 0)) {
            if (promotion_choice == '\0') {
                cout << "Promotion! Choose piece (Q, R, B, N): ";
                cin >> promotion_choice;
            }
            board.promote_pawn(dest, promotion_choice);
        }
    }

    bool check = board.is_check(opponent);
    if (check) {
        cout << (opponent == White ? "White" : "Black") << " is in check!" << endl;
    }

    if (!board.has_legal_moves(opponent)) {
        if (check) {
            cout << "Checkmate! " << (turn == White ? "White" : "Black") << " wins." << endl;
            result = (turn == White ? "1-0" : "0-1");
        } else {
            cout << "Stalemate! It's a draw." << endl;
            result = "1/2-1/2";
        }
        game_over = true;
    }

    // Manage en passant square for next move
    if (moved_piece_is_pawn && 
        abs(dest.getRow() - orig.getRow()) == 2) {
        // Pawn moved two squares - set en passant square to the square it passed through
        int en_passant_row = orig.getRow() + (dest.getRow() - orig.getRow()) / 2;
        board.set_en_passant_square(Square(en_passant_row, dest.getCol()));
    } else {
        // Clear en passant square for non-pawn moves or single square pawn moves
        board.set_en_passant_square(Square(-1, -1));
    }

    if (turn == Black) turn_count++;
    turn = opponent;
}
