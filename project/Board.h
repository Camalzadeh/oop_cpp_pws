#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include "Piece.h"
#include "Square.h"

class Board {
private:
    Piece* board[8][8];
    std::vector<Piece*> pieces[2];
    bool hasEnPassant;
    Square enPassantTarget;
    Square enPassantPawn;
    bool lastForceMoveHadMoved;

    void removePieceFromList(Piece* piece);
    void addPieceToList(Piece* piece);
    bool isPawnPromotionMove(Piece* piece, Square destination) const;
    bool isEnPassantMove(Piece* piece, Square destination) const;
    bool wouldLeaveKingInCheck(Square origin, Square destination, Color color);
    bool canPieceAttackSquare(const Piece* piece, Square square) const;
    bool canCastle(Color turn, bool kingside, std::string& error) const;
    void setBoardSquare(Square square, Piece* piece);

public:
    Board();
    ~Board();

    void display() const;
    Piece* getPiece(Square square) const;
    void placePiece(Piece* piece, Square square);
    bool move(Square origin, Square destination, Color turn, std::string& error);
    bool castle(Color turn, bool kingside, std::string& error);
    bool promotePawn(Square square, char choice, std::string& error);
    bool isSquareEmpty(Square square) const;
    bool isPathClear(Square origin, Square destination) const;

    std::string canonicalPosition() const;
    std::string pgnPieceName(const Piece* piece, bool viewPawn, bool viewColor) const;

    Square findKing(Color color) const;
    bool isSquareAttacked(Square square, Color attackerColor) const;
    bool isCheck(Color kingColor) const;

    // Reversible simulation used by check, checkmate, stalemate, and castling tests.
    void forceMove(Square origin, Square destination, Piece*& captured);
    void undoForceMove(Square origin, Square destination, Piece* captured);

    bool hasLegalMoves(Color color);
    bool needsPromotion(Square square) const;
};

#endif
