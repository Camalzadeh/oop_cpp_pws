#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>

class Fraction {
private:
    int num;
    int den;

    int pgcd(int a, int b) const;

public:
    Fraction();
    Fraction(int n, int d);

    Fraction add(const Fraction& f) const;
    Fraction multiply(const Fraction& f) const;
    void display() const;
    Fraction simplify() const;

    Fraction operator+(const Fraction& f) const;
    Fraction operator*(const Fraction& f) const;

    friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
};

#endif
