#ifndef JEU_H
#define JEU_H

#include <string>
#include "Echiquier.h"

class Jeu {
private:
    Echiquier board;
    Color turn;
    std::string result;
    bool game_over;

public:
    Jeu();
    void affiche() const;
    void deplace(std::string orig, std::string dest);
    bool is_game_over() const { return game_over; }
    void set_result(std::string res) { result = res; game_over = true; }
    std::string get_result() const { return result; }
    std::string get_canonical() const { return board.canonical_position(); }
};

#endif
