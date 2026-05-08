#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "Board.h"

class Game {
private:
    Board board;
    Color turn;
    std::string result;
    bool gameOver;
    int turnCount;
    std::vector<std::string> pendingStatusMessages;

    void finishTurn();
    bool askPromotion(Square square, char initialChoice = '\0');

public:
    Game();
    void display() const;
    void flushStatusMessages();
    void move(std::string origin, std::string destination, char promotionChoice = '\0');
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
