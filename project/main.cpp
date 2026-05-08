#include "Game.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

bool is_castle_symbol(char c) {
    return c == 'O' || c == 'o' || c == '0';
}

bool is_kingside_castle(const string& move) {
    return move.length() == 3 &&
           is_castle_symbol(move[0]) &&
           move[1] == '-' &&
           is_castle_symbol(move[2]);
}

bool is_queenside_castle(const string& move) {
    return move.length() == 5 &&
           is_castle_symbol(move[0]) &&
           move[1] == '-' &&
           is_castle_symbol(move[2]) &&
           move[3] == '-' &&
           is_castle_symbol(move[4]);
}

bool is_promotion_piece(char c) {
    return c == 'Q' || c == 'q' ||
           c == 'R' || c == 'r' ||
           c == 'B' || c == 'b' ||
           c == 'N' || c == 'n';
}

int main() {
    Game mygame;
    string move_input;
    bool stop(false);
    bool quiet = std::getenv("CHESS_QUIET") != nullptr;
    
    if (!quiet) mygame.display();
    
    while (!stop && !mygame.is_game_over()) {
        if (!quiet) {
            cout << mygame.get_turn_count() << ". " 
                 << (mygame.get_turn_color() == White ? "White" : "Black") 
                 << " -> (eg. d2d4) ? ";
        }
             
        if (!(cin >> move_input)) break;

        if (move_input == "/quit" || move_input == "/exit") {
            mygame.set_result("?-?");
            stop = true;
        } else if (move_input == "/resign") {
            mygame.set_result(mygame.get_turn_color() == White ? "0-1" : "1-0");
            stop = true;
        } else if (move_input == "/draw") {
            mygame.set_result("1/2-1/2");
            stop = true;
        } else if (is_kingside_castle(move_input) || is_queenside_castle(move_input)) {
            bool whiteTurn = mygame.get_turn_color() == White;
            string orig = whiteTurn ? "e1" : "e8";
            string dest = is_kingside_castle(move_input)
                ? (whiteTurn ? "g1" : "g8")
                : (whiteTurn ? "c1" : "c8");
            mygame.move(orig, dest);
            if (!quiet && !mygame.is_game_over()) mygame.display();
        } else if (move_input.length() == 4) {
            string orig = move_input.substr(0, 2);
            string dest = move_input.substr(2, 2);
            mygame.move(orig, dest);
            if (!quiet && !mygame.is_game_over()) mygame.display();
        } else if (move_input.length() == 5 && is_promotion_piece(move_input[4])) {
            string orig = move_input.substr(0, 2);
            string dest = move_input.substr(2, 2);
            mygame.move(orig, dest, move_input[4]);
            if (!quiet && !mygame.is_game_over()) mygame.display();
        } else {
            cout << "Invalid command." << endl;
        }
    }

    cout << endl << mygame.get_canonical() << " " << mygame.get_result() << endl;
    return 0;
}
