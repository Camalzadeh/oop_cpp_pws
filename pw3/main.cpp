#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*******************************************
 * Complete the program from here onward.
 *******************************************/

class Auteur {
private:
    string name;
    bool award;

public:
    Auteur(string n, bool a = false) : name(n), award(a) {}
    Auteur(const Auteur& other) : name(other.name), award(other.award) {}
    
    string getNom() const { return name; }
    bool get_prix() const { return award; }
};

class Oeuvre {
private:
    string title;
    const Auteur& author;
    string language;

public:
    Oeuvre(string t, const Auteur& a, string l) : title(t), author(a), language(l) {}
    
    ~Oeuvre() {
        cout << "The work \"" << title << ", " << author.getNom() << ", in " << language << "\" is no longer available." << endl;
    }

    string getTitre() const { return title; }
    const Auteur& getAuteur() const { return author; }
    string getLangue() const { return language; }

    void affiche() const {
        cout << title << ", " << author.getNom() << ", in " << language << endl;
    }
};

class Exemplaire {
private:
    const Oeuvre& oeuvre;

public:
    Exemplaire(const Oeuvre& o) : oeuvre(o) {
        cout << "New copy of: ";
        oeuvre.affiche();
    }

    Exemplaire(const Exemplaire& other) : oeuvre(other.oeuvre) {
        cout << "Copy of a copy of \"";
        cout << oeuvre.getTitre() << ", " << oeuvre.getAuteur().getNom() << ", in " << oeuvre.getLangue();
        cout << "\"" << endl;
    }

    ~Exemplaire() {
        cout << "A copy of \"" << oeuvre.getTitre() << ", " << oeuvre.getAuteur().getNom() << ", in " << oeuvre.getLangue() << "\" has been discarded!" << endl;
    }

    const Oeuvre& getOeuvre() const { return oeuvre; }
};

class Bibliotheque {
private:
    string nom;
    vector<Exemplaire*> exemplaires;

public:
    Bibliotheque(string n) : nom(n) {
        cout << "The " << nom << " library is open!" << endl;
    }

    ~Bibliotheque() {
        cout << "The " << nom << " library is closing its doors," << endl;
        cout << " and destroying its copies:" << endl;
        for (size_t i = 0; i < exemplaires.size(); ++i) {
            delete exemplaires[i];
        }
    }

    string getNom() const { return nom; }

    void stocker(const Oeuvre& o, int n = 1) {
        for (int i = 0; i < n; ++i) {
            exemplaires.push_back(new Exemplaire(o));
        }
    }

    void lister_exemplaires(string langue = "") {
        for (auto e : exemplaires) {
            if (langue == "" || e->getOeuvre().getLangue() == langue) {
                cout << "Copy of: ";
                e->getOeuvre().affiche();
            }
        }
    }

    void afficher_auteurs(bool prix_only = false) {
        for (auto e : exemplaires) {
            if (!prix_only || e->getOeuvre().getAuteur().get_prix()) {
                cout << e->getOeuvre().getAuteur().getNom() << endl;
            }
        }
    }

    int compter_exemplaires(const Oeuvre& o) {
        int count = 0;
        for (auto e : exemplaires) {
            if (&e->getOeuvre() == &o) {
                count++;
            }
        }
        return count;
    }
};

/*******************************************
 * Do not modify anything after this line.
 *******************************************/

int main()
{
  Auteur a1("Victor Hugo"),
         a2("Alexandre Dumas"),
         a3("Raymond Queneau", true);

  Oeuvre o1("Les Misérables"           , a1, "français" ),
         o2("L'Homme qui rit"          , a1, "français" ),
         o3("Le Comte de Monte-Cristo" , a2, "français" ),
         o4("Zazie dans le métro"      , a3, "français" ),
         o5("The Count of Monte-Cristo", a2, "anglais" );

  Bibliotheque biblio("municipale");
  biblio.stocker(o1, 2);
  biblio.stocker(o2);
  biblio.stocker(o3, 3);
  biblio.stocker(o4);
  biblio.stocker(o5);

  cout << "La bibliothèque " << biblio.getNom()
       << " offre les exemplaires suivants :" << endl;
  biblio.lister_exemplaires();

  const string langue("anglais");
  cout << " Les exemplaires en "<< langue << " sont :" << endl;
  biblio.lister_exemplaires(langue);

  cout << " Les auteurs à succès sont :" << endl;
  biblio.afficher_auteurs(true);

  cout << " Il y a " << biblio.compter_exemplaires(o3) << " exemplaires de "
       << o3.getTitre() << endl;

  return 0;
}
