#include "Marchand.h"
#include "Personnage.h"
#include <iostream>

using namespace std;

Marchand::Marchand(const std::string& n, int x, int y)
    : Entite(n,0, x, y,0,0,0)
{
    // Stock fixe du marchand
    stock.push_back(Objet("Robot Chirurgien", TypeObjet::Robot_Chirurgien, 20));
    stock.push_back(Objet("Robot Chirurgien", TypeObjet::Robot_Chirurgien, 20));
    stock.push_back(Objet("Seringue de steroids", TypeObjet::Seringue_de_steroid, 15));
    stock.push_back(Objet("Les chaussures qui courent vite", TypeObjet::Chaussures_qui_courent_vite, 40));
    stock.push_back(Objet("PortalGun", TypeObjet::PortalGun, 0));
}

void Marchand::parler()
{
    cout << endl << "Marchand : Salut voyageur ! Je vends quelques objets utiles.\n";
    cout << "Voici mon stock :\n" << endl;
    cout << "__________________________________"<<endl;
    for (size_t i = 0; i < stock.size(); ++i)
    {
        cout << i << " - " << stock[i].GetNom() << " (valeur : " << stock[i].GetValeur() << ")\n";
    }
    cout << "__________________________________"<<endl;
    cout << "Entrez le numéro de l'objet pour l'acheter ou -1 pour partir : ";
}

void Marchand::vendreObjet(int index, Personnage& joueur)
{
    if (index < 0 || index >= stock.size())
    {
        std::cout << "Objet invalide.\n";
        return;
    }

    Objet& o = stock[index];
    int prix = 30; // fixe pour simplifier
    if (joueur.GetArgent() < prix)
    {
        std::cout << "Pas assez d'argent.\n";
        return;
    }

    joueur.MAJPV(0); // optionnel si tu veux afficher stats après achat
    joueur.ajouterObjet(new Objet(o.GetNom(), o.GetType(), o.GetValeur()));
    joueur.MAJArgent(-prix);
    std::cout << "Achat réussi : " << o.GetNom() << "\n";

    // retirer du stock
    stock.erase(stock.begin() + index);
}
