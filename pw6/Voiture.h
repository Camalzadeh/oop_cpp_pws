#ifndef VOITURE_H
#define VOITURE_H

#include "Vehicule.h"

class Voiture : public Vehicule {
private:
    size_t doors;

public:
    Voiture(std::string b, std::string m, size_t d, double p) : Vehicule(b, m, p), doors(d) {
        std::cout << "-> Car " << brand << " " << model << " created" << std::endl;
    }

    void afficher() const override {
        std::cout << "[Car] brand:" << brand << ", model:" << model << " (daily price: " << price << " Eur)  (" << doors << " doors)" << std::endl;
    }
};

#endif
