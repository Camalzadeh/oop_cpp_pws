#ifndef AGENCE_H
#define AGENCE_H

#include <vector>
#include <string>
#include "Vehicule.h"

class Agence {
private:
    std::string name;
    std::vector<Vehicule*> fleet;

public:
    Agence(std::string n);
    ~Agence();

    void ajouter_flotte(Vehicule* v);
    void afficher_flotte() const;
};

#endif
