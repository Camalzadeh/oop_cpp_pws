#include "Game.h"
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

static string normalizedCastleCommand(string command) {
    replace(command.begin(), command.end(), '0', 'O');
    for (char& ch : command) {
        ch = static_cast<char>(toupper(static_cast<unsigned char>(ch)));
    }
    return command;
}

static bool isPromotionPiece(char ch) {
    ch = static_cast<char>(toupper(static_cast<unsigned char>(ch)));
    return ch == 'Q' || ch == 'R' || ch == 'B' || ch == 'N';
}

int main() {
    Game game;
    string moveText;
    bool quiet = getenv("CHESS_QUIET") != nullptr;

    if (!quiet) {
        game.display();
    }
    while (!game.isGameOver()) {
        if (!quiet) {
            cout << game.currentTurnCount() << ". "
                 << (game.currentTurn() == White ? "White" : "Black")
                 << " -> (eg. e2e4) ? ";
        }
        if (!(cin >> moveText)) {
            break;
        }

        if (moveText == "/quit" || moveText == "/exit") {
            game.setResult("?-?");
        } else if (moveText == "/draw") {
            game.setResult("1/2-1/2");
        } else if (moveText == "/resign") {
            game.setResult(game.currentTurn() == White ? "0-1" : "1-0");
        } else {
            string castleCommand = normalizedCastleCommand(moveText);
            if (castleCommand == "O-O") {
                game.castle(true);
            } else if (castleCommand == "O-O-O") {
                game.castle(false);
            } else if (moveText.length() == 4) {
                string origin = moveText.substr(0, 2);
                string destination = moveText.substr(2, 2);
                game.move(origin, destination);
            } else if (moveText.length() == 5 && isPromotionPiece(moveText[4])) {
                string origin = moveText.substr(0, 2);
                string destination = moveText.substr(2, 2);
                game.move(origin, destination, moveText[4]);
            } else {
                cout << "Invalid command." << endl;
            }

            if (!quiet) {
                game.display();
            }
            game.flushStatusMessages();
        }
    }

    cout << endl << game.getCanonical() << " " << game.getResult() << endl;
    return 0;
}
