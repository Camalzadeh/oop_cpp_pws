#include "Game.h"
#include <iostream>

using namespace std;

Game::Game() : turn(White), result("?-?"), game_over(false), turn_count(1) {}

void Game::display() const {
    board.display();
}

void Game::move(string orig_str, string dest_str) {
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

    Piece* captured = nullptr;
    board.force_move(orig, dest, captured);
    if (board.is_check(turn)) {
        board.undo_force_move(orig, dest, captured);
        cout << "Move leaves king in check." << endl;
        return;
    }

    Color opponent = (turn == White ? Black : White);
    bool check = board.is_check(opponent);
    if (check) {
        cout << (opponent == White ? "White" : "Black") << " is in check!" << endl;
    }

    if (board.pgn_piece_name(p->to_string(), true, false) == "P") {
        if (dest.getRow() == (p->getColor() == White ? 7 : 0)) {
            cout << "Promotion! Choose piece (Q, R, B, N): ";
            // Simplified: always Promote to Queen for now to keep flow
            // Real implementation would take input
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

    if (turn == Black) turn_count++;
    turn = opponent;
}
