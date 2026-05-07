#ifndef GAME_H
#define GAME_H

#include <string>
#include "Board.h"

class Game {
private:
    Board board;
    Color turn;
    std::string result;
    bool game_over;
    int turn_count;

public:
    Game();
    void display() const;
    void move(std::string orig, std::string dest);
    bool is_game_over() const { return game_over; }
    void set_result(std::string res) { result = res; game_over = true; }
    std::string get_result() const { return result; }
    std::string get_canonical() const { return board.canonical_position(); }
    
    int get_turn_count() const { return turn_count; }
    Color get_turn_color() const { return turn; }
};

#endif
