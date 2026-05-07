#include "Game.h"
#include <algorithm>
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

int main() {
    Game game;
    string moveText;

    game.display();
    while (!game.isGameOver()) {
        cout << "Move (eg. e2e4) ? ";
        if (!(cin >> moveText)) {
            break;
        }

        if (moveText == "/quit") {
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
            } else {
                cout << "Invalid command." << endl;
            }

            if (!game.isGameOver()) {
                game.display();
            }
        }
    }

    cout << endl << game.getCanonical() << " " << game.getResult() << endl;
    return 0;
}
