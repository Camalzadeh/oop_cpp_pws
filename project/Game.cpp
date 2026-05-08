#include "Game.h"
#include <cctype>
#include <iostream>

using namespace std;

Game::Game() : turn(White), result("?-?"), gameOver(false), turnCount(1) {}

void Game::display() const {
    board.display();
}

bool Game::askPromotion(Square square) {
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
        cout << (opponent == White ? "White" : "Black") << " is in check!" << endl;
    }

    if (!board.hasLegalMoves(opponent)) {
        if (check) {
            cout << "Checkmate! " << (turn == White ? "White" : "Black") << " wins." << endl;
            result = (turn == White) ? "1-0" : "0-1";
        } else {
            cout << "Stalemate! It's a draw." << endl;
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

void Game::move(string originText, string destinationText) {
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
    if (board.needsPromotion(destination) && !askPromotion(destination)) {
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
