#include "Objet.h"
#include <iostream>
#include "Personnage.h"

// Constructeur
Objet::Objet(std::string n, TypeObjet t, int v)
    : nom(n), type(t), valeur(v)
{
}

// Accesseurs
std::string Objet::GetNom() const { return nom; }
TypeObjet Objet::GetType() const { return type; }
int Objet::GetValeur() const { return valeur; }

// Méthode utiliser (placeholder, effet réel à implémenter dans le jeu)
void Objet::utiliser(Personnage& joueur)
{
    switch (type)
    {
    case TypeObjet::Potion:
        std::cout << endl <<"Utilisation de " << nom << " pour soigner " << valeur << " PV.\n";
        joueur.MAJPV(valeur);
        cout << "PV actuels : " << joueur.GetPV() << endl;
        break;

    case TypeObjet::Seringue_de_dopamine:
        std::cout << endl <<"Utilisation de " << nom << " : +" << valeur << " force.\n";
        joueur.augmenterForce(valeur);
        cout << "Force actuelle : " << joueur.GetForce() << endl;
        break;

    case TypeObjet::Argent:
        std::cout << endl << "Récupération de " << valeur << " pièces.\n";
        joueur.ajouterArgent(valeur);
        cout << "Argent actuel : " << joueur.GetArgent() << endl;
        break;

    case TypeObjet::PortalGun:
        std::cout << endl <<"ZZziiouuwwff ! Retour à la case précédente.\n";
        joueur.revenirCasePrecedente();
        break;

    default:
        std::cout << "Objet inconnu.\n";
        break;
    }
}




