#ifndef SQUARE_H
#define SQUARE_H

#include <string>

class Square {
private:
    int row;
    int col;

public:
    Square(int r = 0, int c = 0) : row(r), col(c) {}
    Square(std::string name) {
        if (name.length() >= 2) {
            col = name[0] - 'a';
            row = name[1] - '1';
        } else {
            row = -1;
            col = -1;
        }
    }

    int getRow() const { return row; }
    int getCol() const { return col; }

    bool isValid() const {
        return row >= 0 && row < 8 && col >= 0 && col < 8;
    }

    std::string to_string() const {
        std::string s = "";
        s += (char)('a' + col);
        s += (char)('1' + row);
        return s;
    }

    bool operator==(const Square& other) const {
        return row == other.row && col == other.col;
    }
};

#endif
