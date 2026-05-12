#include "fraction.hpp"
#include <iostream>

int Fraction::pgcd(int a, int b) const {
    a = (a < 0) ? -a : a;
    b = (b < 0) ? -b : b;
    
    if (b == 0) return a;
    int r = a % b;
    if (r == 0)
        return b;
    else
        return pgcd(b, r);
}

Fraction::Fraction() : num(1), den(1) {}

Fraction::Fraction(int n, int d) : num(n), den(d) {
    if (den == 0) {
        std::cerr << "Error: Denominator cannot be zero. Setting to 1." << std::endl;
        den = 1;
    }
}

Fraction Fraction::add(const Fraction& f) const {
    return Fraction(num * f.den + f.num * den, den * f.den);
}

Fraction Fraction::multiply(const Fraction& f) const {
    return Fraction(num * f.num, den * f.den);
}

void Fraction::display() const {
    std::cout << num << "/" << den << std::endl;
}

Fraction Fraction::simplify() const {
    if (num == 0) return Fraction(0, 1);
    int common = pgcd(num, den);
    return Fraction(num / common, den / common);
}

Fraction Fraction::operator+(const Fraction& f) const {
    return this->add(f);
}

Fraction Fraction::operator*(const Fraction& f) const {
    return this->multiply(f);
}

std::ostream& operator<<(std::ostream& os, const Fraction& f) {
    os << f.num << "/" << f.den;
    return os;
}
