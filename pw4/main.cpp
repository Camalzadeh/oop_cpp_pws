#include "sentence.hpp"
#include <iostream>

using namespace std;

int main() {
    Sentence s1("hello world");
    Sentence s2(s1);  // copy of s1 into s2

    cout << "s1=" << s1 << " and s2=" << s2 << endl;
    return 0;
}
