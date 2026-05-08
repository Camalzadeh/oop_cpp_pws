#include "Board.h"
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

Board::Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = nullptr;
        }
    }
    
    en_passant_square = Square(-1, -1);

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
        // record captured piece for display
        record_capture(target, p->getColor());
        auto& v = pieces[target->getColor()];
        v.erase(std::remove(v.begin(), v.end(), target), v.end());
        delete target;
    }

    board[dest.getRow()][dest.getCol()] = p;
    board[orig.getRow()][orig.getCol()] = nullptr;
    p->setPos(dest);
}

void Board::record_capture(Piece* p, Color capturer) {
    if (!p) return;
    capturedPieces[capturer].push_back(p->to_string());
}

void Board::unrecord_last_capture(Color capturer) {
    if (!capturedPieces[capturer].empty()) capturedPieces[capturer].pop_back();
}

int Board::material_score(Color c) const {
    int score = 0;
    for (auto p : pieces[c]) {
        std::string sym = pgn_piece_name(p->to_string(), true, false);
        if (sym == "P") score += 1;
        else if (sym == "N" || sym == "B") score += 3;
        else if (sym == "R") score += 5;
        else if (sym == "Q") score += 9;
    }
    return score;
}

bool Board::is_path_clear(Square orig, Square dest) const {
    // Prevent moving to the same square
    if (orig == dest) return false;
    
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
                cout << " " << pgn_piece_name(board[i][j]->to_string(), true, true) << "  ";
            } else {
                cout << "     ";
            }
        }
        cout << "| " << i + 1 << "\n  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    }
    cout << "     a     b     c     d     e     f     g     h    " << endl;

    // Show material balance in a chess.com-style console bar.
    int whiteScore = material_score(White);
    int blackScore = material_score(Black);
    int totalScore = whiteScore + blackScore;
    int advantage = whiteScore - blackScore;
    const int barWidth = 32;
    int whiteCells = (totalScore == 0)
        ? barWidth / 2
        : (whiteScore * barWidth + totalScore / 2) / totalScore;
    whiteCells = std::max(0, std::min(barWidth, whiteCells));
    int blackCells = barWidth - whiteCells;

    string advantageText = (advantage > 0 ? "+" : "") + std::to_string(advantage);
    string leader = advantage > 0 ? "White" : (advantage < 0 ? "Black" : "Even");

    cout << "\nMaterial balance" << endl;
    cout << "White " << whiteScore << " ["
         << string(whiteCells, 'W')
         << string(blackCells, 'B')
         << "] " << blackScore << " Black"
         << "   Advantage: " << advantageText << " " << leader << endl;

    cout << "White captured: ";
    for (auto &s : capturedPieces[White]) cout << pgn_piece_name(s, true, true) << " ";
    cout << "\nBlack captured: ";
    for (auto &s : capturedPieces[Black]) cout << pgn_piece_name(s, true, true) << " ";
    cout << "\n";
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

void Board::force_move(Square orig, Square dest, Piece*& captured, bool& moved_before) {
    Piece* p = get_piece(orig);
    moved_before = p->getHasMoved();
    captured = get_piece(dest);
    if (captured) {
        // record capture for display and remove from active pieces
        record_capture(captured, p->getColor());
        auto& v = pieces[captured->getColor()];
        v.erase(std::remove(v.begin(), v.end(), captured), v.end());
    }
    board[dest.getRow()][dest.getCol()] = p;
    board[orig.getRow()][orig.getCol()] = nullptr;
    p->setPos(dest);
}

void Board::undo_force_move(Square orig, Square dest, Piece* captured, bool moved_before) {
    Piece* p = get_piece(dest);
    board[orig.getRow()][orig.getCol()] = p;
    board[dest.getRow()][dest.getCol()] = captured;
    p->restoreState(orig, moved_before);
    if (captured) {
        // remove the last recorded capture for the capturer
        Color capturer = (captured->getColor() == White ? Black : White);
        unrecord_last_capture(capturer);
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
                    bool moved_before = false;
                        Piece* en_passant_victim = nullptr;
                        bool is_en_passant = false;
                        Square orig = p->getPos();
                        if (pgn_piece_name(p->to_string(), true, false) == "P" &&
                            dest == en_passant_square &&
                            std::abs(dest.getCol() - orig.getCol()) == 1) {
                            is_en_passant = true;
                            Square victim_square(orig.getRow(), dest.getCol());
                            en_passant_victim = get_piece(victim_square);
                            if (en_passant_victim) {
                                auto& v = pieces[en_passant_victim->getColor()];
                                v.erase(std::remove(v.begin(), v.end(), en_passant_victim), v.end());
                                board[victim_square.getRow()][victim_square.getCol()] = nullptr;
                            }
                        }

                        force_move(orig, dest, captured, moved_before);
                    bool check = is_check(c);
                        undo_force_move(orig, dest, captured, moved_before);
                        if (is_en_passant && en_passant_victim) {
                            Square victim_square(orig.getRow(), dest.getCol());
                            board[victim_square.getRow()][victim_square.getCol()] = en_passant_victim;
                            pieces[en_passant_victim->getColor()].push_back(en_passant_victim);
                        }
                    if (!check) return true;
                }
            }
        }
    }
    return false;
}

void Board::promote_pawn(Square pos, char piece_type) {
    Piece* pawn = get_piece(pos);
    if (!pawn) return;
    
    Color color = pawn->getColor();
    auto& v = pieces[color];
    
    // Remove the pawn from the pieces vector
    v.erase(std::remove(v.begin(), v.end(), pawn), v.end());
    delete pawn;
    
    // Create the promoted piece based on piece_type
    Piece* promoted = nullptr;
    piece_type = std::toupper(piece_type);
    
    switch (piece_type) {
        case 'Q':
            promoted = new Queen(color, color == White ? "\u2655" : "\u265B", pos);
            break;
        case 'R':
            promoted = new Rook(color, color == White ? "\u2656" : "\u265C", pos);
            break;
        case 'B':
            promoted = new Bishop(color, color == White ? "\u2657" : "\u265D", pos);
            break;
        case 'N':
            promoted = new Knight(color, color == White ? "\u2658" : "\u265E", pos);
            break;
        default:
            // Default to Queen
            promoted = new Queen(color, color == White ? "\u2655" : "\u265B", pos);
    }
    
    // Add the promoted piece to the pieces vector and board
    v.push_back(promoted);
    place_piece(promoted, pos);
}

void Board::remove_piece(Square pos) {
    Piece* p = get_piece(pos);
    if (!p) return;
    
    Color color = p->getColor();
    auto& v = pieces[color];
    v.erase(std::remove(v.begin(), v.end(), p), v.end());
    delete p;
    place_piece(nullptr, pos);
}

void Board::restore_piece(Piece* p, Square pos) {
    if (!p) return;
    pieces[p->getColor()].push_back(p);
    place_piece(p, pos);
}
