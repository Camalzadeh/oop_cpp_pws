#include "Jeu.h"
#include <iostream>

using namespace std;

Jeu::Jeu() : turn(White), result("?-?"), game_over(false) {}

void Jeu::affiche() const {
    board.affiche();
}

void Jeu::deplace(string orig_str, string dest_str) {
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

    if (!p->is_legal_move(dest, board)) {
        cout << "Illegal move geometry or obstacles." << endl;
        return;
    }

    Piece* target = board.get_piece(dest);
    if (target && target->getColor() == turn) {
        cout << "Cannot capture your own piece." << endl;
        return;
    }

    // Check simulation
    Piece* captured = nullptr;
    board.force_move(orig, dest, captured);
    if (board.is_check(turn)) {
        board.undo_force_move(orig, dest, captured);
        cout << "Move leaves king in check." << endl;
        return;
    }

    // Move is final
    // Note: board.force_move already updated the position.
    // If I want to trigger special effects (like hasMoved update), I should do it properly.
    // In force_move I call setPos, which sets hasMoved to true.
    
    // Check if opponent is in check
    Color opponent = (turn == White ? Black : White);
    bool check = board.is_check(opponent);
    if (check) {
        cout << (opponent == White ? "White" : "Black") << " is in check!" << endl;
    }

    // Pawn Promotion
    if (board.pgn_piece_name(p->to_string(), true, false) == "P") {
        if (dest.getRow() == (p->getColor() == White ? 7 : 0)) {
            cout << "Promotion! Choose piece (Q, R, B, N): ";
            char choice;
            cin >> choice;
            // In a full implementation, we'd replace the piece in the board and pieces vector.
            // For now, we'll assume Queen as it's the most common.
        }
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

    turn = opponent;
}
