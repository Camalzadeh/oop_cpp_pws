#ifndef VEHICULE_H
#define VEHICULE_H

#include <iostream>
#include <string>

class Vehicule {
protected:
    std::string brand;
    std::string model;
    double price;

public:
    Vehicule(std::string b, std::string m, double p) : brand(b), model(m), price(p) {}
    virtual ~Vehicule() {}

    virtual void afficher() const {
        std::cout << "[Vehicle] brand:" << brand << ", model:" << model << " (daily price:" << price << " Eur)" << std::endl;
    }
};

#endif
