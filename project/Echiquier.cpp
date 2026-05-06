#include "Echiquier.h"
#include <iostream>
#include <algorithm>

using namespace std;

Echiquier::Echiquier() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = nullptr;
        }
    }

    // White pieces
    pieces[White] = {
        new Tour(White, "\u2656", Square(0, 0)),
        new Cavalier(White, "\u2658", Square(0, 1)),
        new Fou(White, "\u2657", Square(0, 2)),
        new Dame(White, "\u2655", Square(0, 3)),
        new Roi(White, "\u2654", Square(0, 4)),
        new Fou(White, "\u2657", Square(0, 5)),
        new Cavalier(White, "\u2658", Square(0, 6)),
        new Tour(White, "\u2656", Square(0, 7))
    };
    for (int i = 0; i < 8; i++) {
        pieces[White].push_back(new Pion(White, "\u2659", Square(1, i)));
    }

    // Black pieces
    pieces[Black] = {
        new Tour(Black, "\u265C", Square(7, 0)),
        new Cavalier(Black, "\u265E", Square(7, 1)),
        new Fou(Black, "\u265D", Square(7, 2)),
        new Dame(Black, "\u265B", Square(7, 3)),
        new Roi(Black, "\u265A", Square(7, 4)),
        new Fou(Black, "\u265D", Square(7, 5)),
        new Cavalier(Black, "\u265E", Square(7, 6)),
        new Tour(Black, "\u265C", Square(7, 7))
    };
    for (int i = 0; i < 8; i++) {
        pieces[Black].push_back(new Pion(Black, "\u265F", Square(6, i)));
    }

    for (auto p : pieces[White]) pose_piece(p, p->getPos());
    for (auto p : pieces[Black]) pose_piece(p, p->getPos());
}

Echiquier::~Echiquier() {
    for (auto p : pieces[White]) delete p;
    for (auto p : pieces[Black]) delete p;
}

void Echiquier::pose_piece(Piece* p, Square s) {
    if (s.isValid()) {
        board[s.getRow()][s.getCol()] = p;
    }
}

Piece* Echiquier::get_piece(Square s) const {
    if (s.isValid()) return board[s.getRow()][s.getCol()];
    return nullptr;
}

bool Echiquier::est_case_vide(Square s) const {
    return get_piece(s) == nullptr;
}

void Echiquier::move(Square orig, Square dest) {
    Piece* p = get_piece(orig);
    Piece* target = get_piece(dest);

    if (target != nullptr) {
        // Capture
        auto& v = pieces[target->getColor()];
        v.erase(std::remove(v.begin(), v.end(), target), v.end());
        delete target;
    }

    board[dest.getRow()][dest.getCol()] = p;
    board[orig.getRow()][orig.getCol()] = nullptr;
    p->setPos(dest);
}

bool Echiquier::is_path_clear(Square orig, Square dest) const {
    int r0 = orig.getRow();
    int c0 = orig.getCol();
    int r1 = dest.getRow();
    int c1 = dest.getCol();

    int dr = (r1 > r0) ? 1 : (r1 < r0 ? -1 : 0);
    int dc = (c1 > c0) ? 1 : (c1 < c0 ? -1 : 0);

    int r = r0 + dr;
    int c = c0 + dc;
    while (r != r1 || c != c1) {
        if (!est_case_vide(Square(r, c))) return false;
        r += dr;
        c += dc;
    }
    return true;
}

void Echiquier::affiche() const {
    string space5 = string(5, ' ');
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
                cout << space5;
            }
        }
        cout << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    }
}

string Echiquier::pgn_piece_name(string const name, bool view_pawn, bool view_color) const {
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

string Echiquier::canonical_position() const {
    string output = "";
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Square s(row, col);
            if (!est_case_vide(s)) {
                output += pgn_piece_name(get_piece(s)->to_string(), true, true);
            }
            output += ",";
        }
    }
    return output;
}

Square Echiquier::find_king(Color c) const {
    for (auto p : pieces[c]) {
        if (pgn_piece_name(p->to_string(), false, false) == "K") {
            return p->getPos();
        }
    }
    return Square(-1, -1);
}

bool Echiquier::is_square_attacked(Square s, Color attackerColor) const {
    for (auto p : pieces[attackerColor]) {
        if (p->is_legal_move(s, *this)) return true;
    }
    return false;
}

bool Echiquier::is_check(Color kingColor) const {
    Square kingPos = find_king(kingColor);
    return is_square_attacked(kingPos, (kingColor == White ? Black : White));
}

void Echiquier::force_move(Square orig, Square dest, Piece*& captured) {
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

void Echiquier::undo_force_move(Square orig, Square dest, Piece* captured) {
    Piece* p = get_piece(dest);
    board[orig.getRow()][orig.getCol()] = p;
    board[dest.getRow()][dest.getCol()] = captured;
    p->setPos(orig);
    if (captured) {
        pieces[captured->getColor()].push_back(captured);
    }
}

bool Echiquier::has_legal_moves(Color c) {
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
