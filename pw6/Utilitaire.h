#ifndef UTILITAIRE_H
#define UTILITAIRE_H

#include "Vehicule.h"

class Utilitaire : public Vehicule {
private:
    double volume;

public:
    Utilitaire(std::string b, std::string m, double v, double p) : Vehicule(b, m, p), volume(v) {
        std::cout << "-> Utility vehicle " << brand << " " << model << " created" << std::endl;
    }

    void afficher() const override {
        std::cout << "[Utility vehicle] brand:" << brand << ", model:" << model << " (daily price: " << price << " Eur)  (" << volume << " m3)" << std::endl;
    }
};

#endif
