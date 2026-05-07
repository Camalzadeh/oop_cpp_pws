#include "Game.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    Game mygame;
    string move_input;
    bool stop(false);
    
    mygame.display();
    
    while (!stop && !mygame.is_game_over()) {
        cout << mygame.get_turn_count() << ". " 
             << (mygame.get_turn_color() == White ? "White" : "Black") 
             << " -> (eg. d2d4) ? ";
             
        if (!(cin >> move_input)) break;

        if (move_input == "/quit") {
            mygame.set_result("?-?");
            stop = true;
        } else if (move_input == "/resign") {
            mygame.set_result(mygame.get_turn_color() == White ? "0-1" : "1-0");
            stop = true;
        } else if (move_input == "/draw") {
            mygame.set_result("1/2-1/2");
            stop = true;
        } else if (move_input.length() == 4) {
            string orig = move_input.substr(0, 2);
            string dest = move_input.substr(2, 2);
            mygame.move(orig, dest);
            if (!mygame.is_game_over()) mygame.display();
        } else {
            cout << "Invalid command." << endl;
        }
    }

    cout << mygame.get_canonical() << " " << mygame.get_result() << endl;
    return 0;
}
