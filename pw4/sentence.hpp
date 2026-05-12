#include <cstddef>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

class Sentence {
private:
    size_t nwords;
    string * words;

public:
    Sentence(string input_str) : nwords(0) { 
        int count_space = std::count(input_str.cbegin(), input_str.cend(), ' ');
        words = new string[count_space + 1];

        stringstream ss(input_str);
        while (ss >> words[nwords++]);
        nwords--; 
        cout << "Sentence(\"" << input_str << "\"): nwords=" << nwords << endl;
    }

    Sentence(const Sentence & orig) : nwords(orig.nwords) {
        words = new string[nwords];
        for (size_t i = 0; i < nwords; ++i) {
            words[i] = orig.words[i];
        }
    }

    Sentence& operator=(const Sentence& orig) {
        if (this != &orig) {
            delete[] words;
            nwords = orig.nwords;
            words = new string[nwords];
            for (size_t i = 0; i < nwords; ++i) {
                words[i] = orig.words[i];
            }
        }
        return *this;
    }

    ~Sentence() {
        delete[] words;
    }

    size_t size() const {
        return nwords;
    }

    string & operator[](size_t position) const {
        assert(position < nwords);
        return words[position];
    }
};

std::ostream & operator<<(std::ostream & os, const Sentence & sentence) {
    for (size_t position = 0; position < sentence.size(); ++position) {
        os << sentence[position];
        if (position < sentence.size() - 1) 
            os << "_";
    }
    return os;
}
