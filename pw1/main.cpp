#include "fraction.hpp"
#include <iostream>

using namespace std;

int main() {
    cout << "--- Section 2.3: Basic Operations ---" << endl;
    Fraction f1(1, 2);
    Fraction f2(3, 4);
    Fraction f3 = f2;
    
    Fraction f4 = f3.multiply(f2);
    cout << "f4 (f3 * f2): ";
    f4.display();

    f3 = f1.add(f4);
    cout << "f3 (f1 + f4): ";
    f3.display();

    Fraction f5 = f4.simplify();
    cout << "f5 (simplified f4): ";
    f5.display();

    cout << "\n--- Section 3: Operator Overloading ---" << endl;
    Fraction fo1(1, 2);
    Fraction fo2(3, 5);

    Fraction fo3;
    fo3 = fo1 + fo2;
    cout << "fo1 + fo2 = " << fo3 << endl;
    cout << "(fo1 + fo2) directly: " << (fo1 + fo2) << endl;

    Fraction fo4 = fo1 * fo3;
    cout << "fo1 * fo3 = " << fo4 << endl;

    return 0;
}
