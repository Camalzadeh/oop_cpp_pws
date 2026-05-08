#include "Board.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>

using namespace std;

Board::Board()
    : hasEnPassant(false),
      enPassantTarget(-1, -1),
      enPassantPawn(-1, -1),
      lastForceMoveHadMoved(false) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            board[row][col] = nullptr;
        }
    }

    pieces[White] = {
        new Rook(White, Square(0, 0)),
        new Knight(White, Square(0, 1)),
        new Bishop(White, Square(0, 2)),
        new Queen(White, Square(0, 3)),
        new King(White, Square(0, 4)),
        new Bishop(White, Square(0, 5)),
        new Knight(White, Square(0, 6)),
        new Rook(White, Square(0, 7))
    };
    for (int col = 0; col < 8; col++) {
        pieces[White].push_back(new Pawn(White, Square(1, col)));
    }

    pieces[Black] = {
        new Rook(Black, Square(7, 0)),
        new Knight(Black, Square(7, 1)),
        new Bishop(Black, Square(7, 2)),
        new Queen(Black, Square(7, 3)),
        new King(Black, Square(7, 4)),
        new Bishop(Black, Square(7, 5)),
        new Knight(Black, Square(7, 6)),
        new Rook(Black, Square(7, 7))
    };
    for (int col = 0; col < 8; col++) {
        pieces[Black].push_back(new Pawn(Black, Square(6, col)));
    }

    for (Piece* piece : pieces[White]) {
        placePiece(piece, piece->getPosition());
    }
    for (Piece* piece : pieces[Black]) {
        placePiece(piece, piece->getPosition());
    }
}

Board::~Board() {
    for (Piece* piece : pieces[White]) {
        delete piece;
    }
    for (Piece* piece : pieces[Black]) {
        delete piece;
    }
}

void Board::removePieceFromList(Piece* piece) {
    if (!piece) {
        return;
    }
    vector<Piece*>& list = pieces[piece->getColor()];
    list.erase(remove(list.begin(), list.end(), piece), list.end());
}

void Board::addPieceToList(Piece* piece) {
    if (piece) {
        pieces[piece->getColor()].push_back(piece);
    }
}

void Board::setBoardSquare(Square square, Piece* piece) {
    if (!square.isValid()) {
        return;
    }
    board[square.getRow()][square.getCol()] = piece;
}

void Board::placePiece(Piece* piece, Square square) {
    setBoardSquare(square, piece);
}

Piece* Board::getPiece(Square square) const {
    if (!square.isValid()) {
        return nullptr;
    }
    return board[square.getRow()][square.getCol()];
}

bool Board::isSquareEmpty(Square square) const {
    return getPiece(square) == nullptr;
}

bool Board::isPathClear(Square origin, Square destination) const {
    int rowStep = (destination.getRow() > origin.getRow()) ? 1 :
                  (destination.getRow() < origin.getRow() ? -1 : 0);
    int colStep = (destination.getCol() > origin.getCol()) ? 1 :
                  (destination.getCol() < origin.getCol() ? -1 : 0);

    int row = origin.getRow() + rowStep;
    int col = origin.getCol() + colStep;
    while (row != destination.getRow() || col != destination.getCol()) {
        if (!isSquareEmpty(Square(row, col))) {
            return false;
        }
        row += rowStep;
        col += colStep;
    }
    return true;
}

void Board::display() const {
    cout << endl;
    cout << "     a     b     c     d     e     f     g     h" << endl;
    cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    for (int row = 7; row >= 0; row--) {
        cout << row + 1 << " ";
        for (int col = 0; col < 8; col++) {
            cout << "|";
            Piece* piece = board[row][col];
            if (piece) {
                cout << "  " << piece->displaySymbol() << "  ";
            } else {
                cout << "     ";
            }
        }
        cout << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    }
}

string Board::pgnPieceName(const Piece* piece, bool viewPawn, bool viewColor) const {
    if (!piece || (!viewPawn && piece->pieceCode() == 'P')) {
        return "";
    }

    string name;
    if (viewColor) {
        name += (piece->getColor() == White ? 'w' : 'b');
    }
    name += piece->pieceCode();
    return name;
}

string Board::canonicalPosition() const {
    string output;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (!output.empty()) {
                output += ",";
            }
            Piece* piece = board[row][col];
            if (piece) {
                output += pgnPieceName(piece, true, true);
            }
        }
    }
    return output;
}

Square Board::findKing(Color color) const {
    for (Piece* piece : pieces[color]) {
        if (piece->pieceCode() == 'K') {
            return piece->getPosition();
        }
    }
    return Square(-1, -1);
}

bool Board::canPieceAttackSquare(const Piece* piece, Square square) const {
    if (!piece || !square.isValid()) {
        return false;
    }

    Square origin = piece->getPosition();
    int rowDelta = square.getRow() - origin.getRow();
    int colDelta = square.getCol() - origin.getCol();

    if (piece->pieceCode() == 'P') {
        int direction = (piece->getColor() == White) ? 1 : -1;
        return rowDelta == direction && abs(colDelta) == 1;
    }
    if (piece->pieceCode() == 'K') {
        return abs(rowDelta) <= 1 && abs(colDelta) <= 1 && !(origin == square);
    }
    return piece->isLegalMove(square, *this);
}

bool Board::isSquareAttacked(Square square, Color attackerColor) const {
    for (Piece* piece : pieces[attackerColor]) {
        if (canPieceAttackSquare(piece, square)) {
            return true;
        }
    }
    return false;
}

bool Board::isCheck(Color kingColor) const {
    Square kingPosition = findKing(kingColor);
    if (!kingPosition.isValid()) {
        return false;
    }
    Color attacker = (kingColor == White) ? Black : White;
    return isSquareAttacked(kingPosition, attacker);
}

bool Board::isEnPassantMove(Piece* piece, Square destination) const {
    if (!piece || piece->pieceCode() != 'P' || !hasEnPassant || !(destination == enPassantTarget)) {
        return false;
    }
    int direction = (piece->getColor() == White) ? 1 : -1;
    Square origin = piece->getPosition();
    return destination.getRow() == origin.getRow() + direction &&
           abs(destination.getCol() - origin.getCol()) == 1 &&
           getPiece(destination) == nullptr;
}

bool Board::isPawnPromotionMove(Piece* piece, Square destination) const {
    return piece && piece->pieceCode() == 'P' &&
           destination.getRow() == (piece->getColor() == White ? 7 : 0);
}

void Board::forceMove(Square origin, Square destination, Piece*& captured) {
    Piece* piece = getPiece(origin);
    captured = getPiece(destination);
    lastForceMoveHadMoved = piece ? piece->getHasMoved() : false;
    if (captured) {
        removePieceFromList(captured);
    }
    setBoardSquare(destination, piece);
    setBoardSquare(origin, nullptr);
    if (piece) {
        piece->setPosition(destination);
    }
}

void Board::undoForceMove(Square origin, Square destination, Piece* captured) {
    Piece* piece = getPiece(destination);
    setBoardSquare(origin, piece);
    setBoardSquare(destination, captured);
    if (piece) {
        piece->setPosition(origin, false);
        piece->setHasMoved(lastForceMoveHadMoved);
    }
    if (captured) {
        addPieceToList(captured);
    }
}

bool Board::wouldLeaveKingInCheck(Square origin, Square destination, Color color) {
    Piece* movingPiece = getPiece(origin);
    Piece* captured = getPiece(destination);
    Square capturedSquare = destination;
    bool wasEnPassant = isEnPassantMove(movingPiece, destination);
    bool movingHadMoved = movingPiece ? movingPiece->getHasMoved() : false;

    if (wasEnPassant) {
        capturedSquare = enPassantPawn;
        captured = getPiece(capturedSquare);
    }

    if (captured) {
        removePieceFromList(captured);
        setBoardSquare(capturedSquare, nullptr);
    }

    setBoardSquare(destination, movingPiece);
    setBoardSquare(origin, nullptr);
    if (movingPiece) {
        movingPiece->setPosition(destination);
    }

    bool leavesCheck = isCheck(color);

    setBoardSquare(origin, movingPiece);
    setBoardSquare(destination, nullptr);
    if (movingPiece) {
        movingPiece->setPosition(origin, false);
        movingPiece->setHasMoved(movingHadMoved);
    }
    if (captured) {
        setBoardSquare(capturedSquare, captured);
        addPieceToList(captured);
    }

    return leavesCheck;
}

bool Board::move(Square origin, Square destination, Color turn, string& error) {
    if (!origin.isValid() || !destination.isValid()) {
        error = "Invalid coordinates.";
        return false;
    }

    Piece* piece = getPiece(origin);
    if (!piece) {
        error = "No piece at origin.";
        return false;
    }
    if (piece->getColor() != turn) {
        error = "It's not your turn.";
        return false;
    }

    bool enPassant = isEnPassantMove(piece, destination);
    if (!piece->isLegalMove(destination, *this) && !enPassant) {
        error = "Illegal move geometry or obstacles.";
        return false;
    }

    Piece* target = getPiece(destination);
    if (target && target->getColor() == turn) {
        error = "Cannot capture your own piece.";
        return false;
    }

    if (wouldLeaveKingInCheck(origin, destination, turn)) {
        error = "Move leaves king in check.";
        return false;
    }

    Square oldOrigin = origin;
    bool doubleStepPawn = piece->pieceCode() == 'P' &&
                          abs(destination.getRow() - origin.getRow()) == 2;

    if (enPassant) {
        Piece* capturedPawn = getPiece(enPassantPawn);
        removePieceFromList(capturedPawn);
        setBoardSquare(enPassantPawn, nullptr);
        delete capturedPawn;
    } else if (target) {
        removePieceFromList(target);
        delete target;
    }

    setBoardSquare(destination, piece);
    setBoardSquare(origin, nullptr);
    piece->setPosition(destination);

    hasEnPassant = false;
    if (doubleStepPawn) {
        int middleRow = (oldOrigin.getRow() + destination.getRow()) / 2;
        hasEnPassant = true;
        enPassantTarget = Square(middleRow, oldOrigin.getCol());
        enPassantPawn = destination;
    }

    return true;
}

bool Board::canCastle(Color turn, bool kingside, string& error) const {
    int row = (turn == White) ? 0 : 7;
    Square kingOrigin(row, 4);
    Square rookOrigin(row, kingside ? 7 : 0);
    Color opponent = (turn == White) ? Black : White;

    Piece* king = getPiece(kingOrigin);
    Piece* rook = getPiece(rookOrigin);
    if (!king || !rook || king->pieceCode() != 'K' || rook->pieceCode() != 'R' ||
        king->getColor() != turn || rook->getColor() != turn) {
        error = "Castling pieces are not in their original squares.";
        return false;
    }
    if (king->getHasMoved() || rook->getHasMoved()) {
        error = "Cannot castle after the king or rook has moved.";
        return false;
    }
    if (isCheck(turn)) {
        error = "Cannot castle while in check.";
        return false;
    }

    int firstCol = kingside ? 5 : 1;
    int lastCol = kingside ? 6 : 3;
    for (int col = firstCol; col <= lastCol; col++) {
        if (!isSquareEmpty(Square(row, col))) {
            error = "Cannot castle through occupied squares.";
            return false;
        }
    }

    // The king may not cross or land on an attacked square.
    int step = kingside ? 1 : -1;
    int startCol = kingside ? 5 : 3;
    int endCol = kingside ? 6 : 2;
    for (int col = startCol; kingside ? col <= endCol : col >= endCol; col += step) {
        if (isSquareAttacked(Square(row, col), opponent)) {
            error = "Cannot castle through check.";
            return false;
        }
    }

    return true;
}

bool Board::castle(Color turn, bool kingside, string& error) {
    if (!canCastle(turn, kingside, error)) {
        return false;
    }

    int row = (turn == White) ? 0 : 7;
    Square kingOrigin(row, 4);
    Square rookOrigin(row, kingside ? 7 : 0);
    Square kingDestination(row, kingside ? 6 : 2);
    Square rookDestination(row, kingside ? 5 : 3);
    Piece* king = getPiece(kingOrigin);
    Piece* rook = getPiece(rookOrigin);

    board[kingDestination.getRow()][kingDestination.getCol()] = king;
    board[kingOrigin.getRow()][kingOrigin.getCol()] = nullptr;
    king->setPosition(kingDestination);

    board[rookDestination.getRow()][rookDestination.getCol()] = rook;
    board[rookOrigin.getRow()][rookOrigin.getCol()] = nullptr;
    rook->setPosition(rookDestination);

    hasEnPassant = false;
    return true;
}

bool Board::promotePawn(Square square, char choice, string& error) {
    Piece* pawn = getPiece(square);
    if (!needsPromotion(square)) {
        error = "No pawn can be promoted on that square.";
        return false;
    }

    choice = static_cast<char>(toupper(static_cast<unsigned char>(choice)));
    Piece* promoted = nullptr;
    if (choice == 'Q') {
        promoted = new Queen(pawn->getColor(), square);
    } else if (choice == 'R') {
        promoted = new Rook(pawn->getColor(), square);
    } else if (choice == 'B') {
        promoted = new Bishop(pawn->getColor(), square);
    } else if (choice == 'N') {
        promoted = new Knight(pawn->getColor(), square);
    } else {
        error = "Promotion choice must be Q, R, B, or N.";
        return false;
    }

    promoted->setHasMoved(true);
    removePieceFromList(pawn);
    delete pawn;
    board[square.getRow()][square.getCol()] = promoted;
    addPieceToList(promoted);
    return true;
}

bool Board::needsPromotion(Square square) const {
    Piece* piece = getPiece(square);
    return piece && isPawnPromotionMove(piece, square);
}

bool Board::hasLegalMoves(Color color) {
    for (Piece* piece : pieces[color]) {
        Square origin = piece->getPosition();
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                Square destination(row, col);
                Piece* target = getPiece(destination);
                if (target && target->getColor() == color) {
                    continue;
                }
                if ((piece->isLegalMove(destination, *this) || isEnPassantMove(piece, destination)) &&
                    !wouldLeaveKingInCheck(origin, destination, color)) {
                    return true;
                }
            }
        }
    }

    string ignored;
    if (canCastle(color, true, ignored) || canCastle(color, false, ignored)) {
        return true;
    }

    return false;
}
