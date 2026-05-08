#include "Game.h"
#include <cctype>
#include <iostream>

using namespace std;

Game::Game() : turn(White), result("?-?"), gameOver(false), turnCount(1) {}

void Game::display() const {
    board.display();
}

void Game::flushStatusMessages() {
    for (const string& message : pendingStatusMessages) {
        cout << message << endl;
    }
    pendingStatusMessages.clear();
}

bool Game::askPromotion(Square square, char initialChoice) {
    if (initialChoice != '\0') {
        string error;
        if (board.promotePawn(square, initialChoice, error)) {
            return true;
        }
        cout << error << endl;
    }

    while (true) {
        cout << "Promotion! Choose piece (Q, R, B, N): ";
        char choice;
        if (!(cin >> choice)) {
            result = "?-?";
            gameOver = true;
            return false;
        }

        string error;
        if (board.promotePawn(square, choice, error)) {
            return true;
        }
        cout << error << endl;
    }
}

void Game::finishTurn() {
    Color opponent = (turn == White) ? Black : White;
    bool check = board.isCheck(opponent);
    if (check) {
        pendingStatusMessages.push_back(
            string(opponent == White ? "White" : "Black") + " is in check!");
    }

    if (!board.hasLegalMoves(opponent)) {
        if (check) {
            pendingStatusMessages.push_back(
                string("Checkmate! ") + (turn == White ? "White" : "Black") + " wins.");
            result = (turn == White) ? "1-0" : "0-1";
        } else {
            pendingStatusMessages.push_back("Stalemate! It's a draw.");
            result = "1/2-1/2";
        }
        gameOver = true;
        return;
    }

    if (turn == Black) {
        turnCount++;
    }
    turn = opponent;
}

void Game::move(string originText, string destinationText, char promotionChoice) {
    Square origin(originText);
    Square destination(destinationText);
    string error;

    int colDelta = destination.getCol() - origin.getCol();
    if (origin.isValid() && destination.isValid() &&
        origin.getRow() == destination.getRow() &&
        (colDelta == 2 || colDelta == -2)) {
        Piece* piece = board.getPiece(origin);
        if (piece && piece->getColor() == turn && piece->pieceCode() == 'K') {
            castle(colDelta > 0);
            return;
        }
    }

    if (!board.move(origin, destination, turn, error)) {
        cout << error << endl;
        return;
    }

    // Promotion replaces the pawn object before the next check/mate calculation.
    if (board.needsPromotion(destination) && !askPromotion(destination, promotionChoice)) {
        return;
    }

    finishTurn();
}

void Game::castle(bool kingside) {
    string error;
    if (!board.castle(turn, kingside, error)) {
        cout << error << endl;
        return;
    }
    finishTurn();
}
