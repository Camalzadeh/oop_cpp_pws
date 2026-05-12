#include <iostream>
#include <vector>
using namespace std;

class Article {
    private:
        string name;
        double price;
        bool isOnSale;
    public: 
        Article(string name, double price, bool isOnSale = false){
            this->name = name;
            this->price = price;
            this->isOnSale = isOnSale;
        }

        string getName()const {
            return name;
        }
        double getPrice()const {
            return price;
        }
        bool getIsOnSale()const {
            return isOnSale;
        }
    
};

class Purchase {
    private:
        Article article;
        int quantity;
    public: 
        Purchase(Article article, int quantity): article(article), quantity(quantity){}

        double evaluate()const {
            double price = article.getPrice();
            bool isOnSale = article.getIsOnSale();
            if (isOnSale){
                price /=2;
            }
            return price*quantity;
        }

        friend ostream& operator<<(ostream& os, const Purchase& p) {
        os << p.article.getName() << " : " 
           << p.article.getPrice() << " x " << p.quantity 
           << " = " << p.evaluate() << " Eur";
        
        if (p.article.getIsOnSale()) {
            os << " (en solde)";
        }
        return os;
    }
};


class Caddie{
    private:
        vector<Purchase> purchases;
    public: 
        Caddie (){}
        void remplir(Article article, int cnt=1){
            purchases.push_back({article, cnt});
        }
        double evaluatePurchases(){
            double total = 0;
            for (auto purchase: purchases){
                cout << purchase << '\n';
                total += purchase.evaluate();
            }
            return total;
        }
};

class Caisse {
    private:
        double total;
    public: 
        Caisse(){
            total = 0;
        }
        void scanner(Caddie caddie){
            double subTotal = caddie.evaluatePurchases();
            cout<< "-----\n";
            cout<< "Total à payer : "<< subTotal<<" Eur.\n";
            total += subTotal;
        }

        void afficher(){
            cout << "total: " << total << " Eur";
        }
};



int main()
{


  Article choufleur ("Chou-fleur extra"     ,  3.50 );
  Article roman     ("Les malheurs de Sophie", 16.50, true );
  Article camembert ("Cremeux 100%MG"        ,  5.80 );
  Article cdrom     ("C++ en trois jours"    , 48.50 );
  Article boisson   ("Chocolats"             ,  2.50, true);
  Article petitspois("Pois surgeles"         ,  4.35 );
  Article poisson   ("Sardines"              ,  6.50 );
  Article biscuits  ("Cookies de grand-mere" ,  3.20 );
  Article poires    ("Poires Williams"       ,  4.80 );
  Article cafe      ("100% Arabica"          ,  6.90, true);
  Article pain      ("Pain d'epautre"        ,  6.90 );

  // The supermarket's shopping carts, let's say 3 here
  vector<Caddie> caddies(3);

  // The supermarket's cash registers, let's say 2
  vector<Caisse> caisses(2);

  // The customers make their purchases:
  // the second argument of the remplir method corresponds to a quantity

  // filling the 1st cart
  caddies[0].remplir(choufleur, 2);
  caddies[0].remplir(cdrom       );
  caddies[0].remplir(biscuits , 4);
  caddies[0].remplir(boisson  , 6);
  caddies[0].remplir(poisson  , 2);

  // filling the 2nd cart
  caddies[1].remplir(roman        );
  caddies[1].remplir(camembert    );
  caddies[1].remplir(petitspois, 2);
  caddies[1].remplir(poires    , 2);

  // filling the 3rd cart
  caddies[2].remplir(cafe     , 2);
  caddies[2].remplir(pain        );
  caddies[2].remplir(camembert, 2);

  // Customers go to the checkout:
  caisses[0].scanner(caddies[0]);
  cout << "=========================================" << endl;
  caisses[0].scanner(caddies[1]);
  cout << "=========================================" << endl;
  caisses[1].scanner(caddies[2]);
  cout << "=========================================" << endl;

  // Display of the cash registers' results
  cout << "Résultats du jour :" << endl;
  for (size_t i(0); i < caisses.size(); ++i) {
    cout << "Caisse " << i+1 << " : " ;
    caisses[i].afficher();
    cout << endl;
  }
  return 0;
}