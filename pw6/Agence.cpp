#include "Agence.h"
#include <iostream>

Agence::Agence(std::string n) : name(n) {}

Agence::~Agence() {
    std::cout << " -> The agency " << name << " closes its doors." << std::endl;
    for (Vehicule* v : fleet) {
        delete v;
    }
}

void Agence::ajouter_flotte(Vehicule* v) {
    fleet.push_back(v);
}

void Agence::afficher_flotte() const {
    for (Vehicule* v : fleet) {
        v->afficher();
    }
}
