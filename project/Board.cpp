#include "Board.h"
#include <iostream>
#include <algorithm>

using namespace std;

Board::Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = nullptr;
        }
    }

    pieces[White] = {
        new Rook(White, "\u2656", Square(0, 0)),
        new Knight(White, "\u2658", Square(0, 1)),
        new Bishop(White, "\u2657", Square(0, 2)),
        new Queen(White, "\u2655", Square(0, 3)),
        new King(White, "\u2654", Square(0, 4)),
        new Bishop(White, "\u2657", Square(0, 5)),
        new Knight(White, "\u2658", Square(0, 6)),
        new Rook(White, "\u2656", Square(0, 7))
    };
    for (int i = 0; i < 8; i++) {
        pieces[White].push_back(new Pawn(White, "\u2659", Square(1, i)));
    }

    pieces[Black] = {
        new Rook(Black, "\u265C", Square(7, 0)),
        new Knight(Black, "\u265E", Square(7, 1)),
        new Bishop(Black, "\u265D", Square(7, 2)),
        new Queen(Black, "\u265B", Square(7, 3)),
        new King(Black, "\u265A", Square(7, 4)),
        new Bishop(Black, "\u265D", Square(7, 5)),
        new Knight(Black, "\u265E", Square(7, 6)),
        new Rook(Black, "\u265C", Square(7, 7))
    };
    for (int i = 0; i < 8; i++) {
        pieces[Black].push_back(new Pawn(Black, "\u265F", Square(6, i)));
    }

    for (auto p : pieces[White]) place_piece(p, p->getPos());
    for (auto p : pieces[Black]) place_piece(p, p->getPos());
}

Board::~Board() {
    for (auto p : pieces[White]) delete p;
    for (auto p : pieces[Black]) delete p;
}

void Board::place_piece(Piece* p, Square s) {
    if (s.isValid()) {
        board[s.getRow()][s.getCol()] = p;
    }
}

Piece* Board::get_piece(Square s) const {
    if (s.isValid()) return board[s.getRow()][s.getCol()];
    return nullptr;
}

bool Board::is_cell_empty(Square s) const {
    return get_piece(s) == nullptr;
}

void Board::move(Square orig, Square dest) {
    Piece* p = get_piece(orig);
    Piece* target = get_piece(dest);

    if (target != nullptr) {
        auto& v = pieces[target->getColor()];
        v.erase(std::remove(v.begin(), v.end(), target), v.end());
        delete target;
    }

    board[dest.getRow()][dest.getCol()] = p;
    board[orig.getRow()][orig.getCol()] = nullptr;
    p->setPos(dest);
}

bool Board::is_path_clear(Square orig, Square dest) const {
    int r0 = orig.getRow();
    int c0 = orig.getCol();
    int r1 = dest.getRow();
    int c1 = dest.getCol();

    int dr = (r1 > r0) ? 1 : (r1 < r0 ? -1 : 0);
    int dc = (c1 > c0) ? 1 : (c1 < c0 ? -1 : 0);

    int r = r0 + dr;
    int c = c0 + dc;
    while (r != r1 || c != c1) {
        if (!is_cell_empty(Square(r, c))) return false;
        r += dr;
        c += dc;
    }
    return true;
}

void Board::display() const {
    cout << endl;
    cout << "     a     b     c     d     e     f     g     h    " << endl;
    cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    for (int i = 7; i >= 0; i--) {
        cout << i + 1 << " ";
        for (int j = 0; j < 8; j++) {
            cout << "|";
            if (board[i][j]) {
                cout << "  " << pgn_piece_name(board[i][j]->to_string(), true, true) << " ";
            } else {
                cout << "     ";
            }
        }
        cout << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    }
}

string Board::pgn_piece_name(string const name, bool view_pawn, bool view_color) const {
    string psymb = "";
    if (name == "\u2656") psymb = "R";
    else if (name == "\u2658") psymb = "N";
    else if (name == "\u2657") psymb = "B";
    else if (name == "\u2655") psymb = "Q";
    else if (name == "\u2654") psymb = "K";
    else if (name == "\u2659" && view_pawn) psymb = "P";
    if (psymb.size() > 0) return view_color ? "w" + psymb : psymb;

    if (name == "\u265C") psymb = "R";
    else if (name == "\u265E") psymb = "N";
    else if (name == "\u265D") psymb = "B";
    else if (name == "\u265B") psymb = "Q";
    else if (name == "\u265A") psymb = "K";
    else if (name == "\u265F" && view_pawn) psymb = "P";
    if (psymb.size() > 0) return view_color ? "b" + psymb : psymb;

    return "";
}

string Board::canonical_position() const {
    string output = "";
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Square s(row, col);
            if (!is_cell_empty(s)) {
                output += pgn_piece_name(get_piece(s)->to_string(), true, true);
            }
            output += ",";
        }
    }
    return output;
}

Square Board::find_king(Color c) const {
    for (auto p : pieces[c]) {
        if (pgn_piece_name(p->to_string(), false, false) == "K") {
            return p->getPos();
        }
    }
    return Square(-1, -1);
}

bool Board::is_square_attacked(Square s, Color attackerColor) const {
    for (auto p : pieces[attackerColor]) {
        if (p->is_legal_move(s, *this)) return true;
    }
    return false;
}

bool Board::is_check(Color kingColor) const {
    Square kingPos = find_king(kingColor);
    return is_square_attacked(kingPos, (kingColor == White ? Black : White));
}

void Board::force_move(Square orig, Square dest, Piece*& captured) {
    Piece* p = get_piece(orig);
    captured = get_piece(dest);
    if (captured) {
        auto& v = pieces[captured->getColor()];
        v.erase(std::remove(v.begin(), v.end(), captured), v.end());
    }
    board[dest.getRow()][dest.getCol()] = p;
    board[orig.getRow()][orig.getCol()] = nullptr;
    p->setPos(dest);
}

void Board::undo_force_move(Square orig, Square dest, Piece* captured) {
    Piece* p = get_piece(dest);
    board[orig.getRow()][orig.getCol()] = p;
    board[dest.getRow()][dest.getCol()] = captured;
    p->setPos(orig);
    if (captured) {
        pieces[captured->getColor()].push_back(captured);
    }
}

bool Board::has_legal_moves(Color c) {
    for (auto p : pieces[c]) {
        for (int r = 0; r < 8; r++) {
            for (int col = 0; col < 8; col++) {
                Square dest(r, col);
                if (p->is_legal_move(dest, *this)) {
                    Piece* target = get_piece(dest);
                    if (target && target->getColor() == c) continue;
                    Piece* captured = nullptr;
                    Square orig = p->getPos();
                    force_move(orig, dest, captured);
                    bool check = is_check(c);
                    undo_force_move(orig, dest, captured);
                    if (!check) return true;
                }
            }
        }
    }
    return false;
}
