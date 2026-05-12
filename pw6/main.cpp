#include "Agence.h"
#include "Vehicule.h"
#include "Utilitaire.h"
#include "Voiture.h"
#include <iostream>

using namespace std;

int main() {
    Agence malocation("MaLocation");

    malocation.ajouter_flotte(new Utilitaire("Mercedes", "Vito", 9., 50.));
    malocation.ajouter_flotte(new Utilitaire("Peugeot", "Master", 9., 45.));
    malocation.ajouter_flotte(new Utilitaire("Renault", "Kangoo", 4., 35.));

    malocation.ajouter_flotte(new Voiture("Peugeot", "207", 5, 25.));
    malocation.ajouter_flotte(new Voiture("Renault", "Clio", 3, 25.));

    malocation.afficher_flotte();

    return 0;
}
