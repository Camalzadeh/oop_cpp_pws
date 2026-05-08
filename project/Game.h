#ifndef GAME_H
#define GAME_H

#include <string>
#include "Board.h"

class Game {
private:
    Board board;
    Color turn;
    std::string result;
    bool gameOver;
    int turnCount;

    void finishTurn();
    bool askPromotion(Square square);

public:
    Game();
    void display() const;
    void move(std::string origin, std::string destination);
    void castle(bool kingside);
    Color currentTurn() const { return turn; }
    int currentTurnCount() const { return turnCount; }
    bool isGameOver() const { return gameOver; }
    void setResult(std::string newResult) {
        result = newResult;
        gameOver = true;
    }
    std::string getResult() const { return result; }
    std::string getCanonical() const { return board.canonicalPosition(); }
};

#endif
