#include "jeu.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    Jeu monjeu;
    string mouvement;
    bool stop(false);
    monjeu.affiche();
    while (!stop) {
        cout << "Move (eg. a1a8) ? ";
        if (!(cin >> mouvement)) break;

        if (mouvement == "/quit") {
            monjeu.set_result("?-?");
            stop = true;
        } else if (mouvement == "/resign") {
            // Need to know whose turn it was to set result
            // Simple version:
            monjeu.set_result("?-?");
            stop = true;
        } else if (mouvement == "/draw") {
            monjeu.set_result("1/2-1/2");
            stop = true;
        } else if (mouvement.length() == 4) {
            string orig = mouvement.substr(0, 2);
            string dest = mouvement.substr(2, 2);
            monjeu.deplace(orig, dest);
            monjeu.affiche();
        } else {
            cout << "Invalid command." << endl;
        }
    }

    cout << monjeu.get_canonical() << " " << monjeu.get_result() << endl;
    return 0;
}
