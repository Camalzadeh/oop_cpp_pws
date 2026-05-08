#include "Piece.h"
#include "Board.h"
#include <cmath>

std::string Piece::toString() const {
    std::string code;
    code += (color == White ? 'w' : 'b');
    code += pieceCode();
    return code;
}

bool Rook::isLegalMove(Square destination, const Board& board) const {
    if (!destination.isValid() || destination == position) {
        return false;
    }
    return (destination.getRow() == position.getRow() ||
            destination.getCol() == position.getCol()) &&
           board.isPathClear(position, destination);
}

bool Knight::isLegalMove(Square destination, const Board& board) const {
    (void)board;
    if (!destination.isValid() || destination == position) {
        return false;
    }
    int rowDelta = std::abs(destination.getRow() - position.getRow());
    int colDelta = std::abs(destination.getCol() - position.getCol());
    return (rowDelta == 2 && colDelta == 1) || (rowDelta == 1 && colDelta == 2);
}

bool Bishop::isLegalMove(Square destination, const Board& board) const {
    if (!destination.isValid() || destination == position) {
        return false;
    }
    int rowDelta = std::abs(destination.getRow() - position.getRow());
    int colDelta = std::abs(destination.getCol() - position.getCol());
    return rowDelta == colDelta && board.isPathClear(position, destination);
}

bool Queen::isLegalMove(Square destination, const Board& board) const {
    if (!destination.isValid() || destination == position) {
        return false;
    }
    int rowDelta = std::abs(destination.getRow() - position.getRow());
    int colDelta = std::abs(destination.getCol() - position.getCol());
    bool diagonal = rowDelta == colDelta;
    bool straight = destination.getRow() == position.getRow() ||
                    destination.getCol() == position.getCol();
    return (diagonal || straight) && board.isPathClear(position, destination);
}

bool King::isLegalMove(Square destination, const Board& board) const {
    (void)board;
    if (!destination.isValid() || destination == position) {
        return false;
    }
    int rowDelta = std::abs(destination.getRow() - position.getRow());
    int colDelta = std::abs(destination.getCol() - position.getCol());
    return rowDelta <= 1 && colDelta <= 1;
}

bool Pawn::isLegalMove(Square destination, const Board& board) const {
    if (!destination.isValid() || destination == position) {
        return false;
    }

    int startRow = (color == White) ? 1 : 6;
    int direction = (color == White) ? 1 : -1;
    int rowDelta = destination.getRow() - position.getRow();
    int colDelta = destination.getCol() - position.getCol();

    if (colDelta == 0) {
        if (rowDelta == direction) {
            return board.isSquareEmpty(destination);
        }
        if (position.getRow() == startRow && rowDelta == 2 * direction) {
            Square middle(position.getRow() + direction, position.getCol());
            return board.isSquareEmpty(middle) && board.isSquareEmpty(destination);
        }
    }

    if (std::abs(colDelta) == 1 && rowDelta == direction) {
        Piece* target = board.getPiece(destination);
        return target != nullptr && target->getColor() != color;
    }

    return false;
}
