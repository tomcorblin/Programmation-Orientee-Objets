#include "Entite.h"
#include <iostream>
using namespace std;

// Constructeur
Entite::Entite(std::string n, int sa, int px, int py, int pv, int f, int r)
    : nom(n), somme_argent(sa), positionX(px), positionY(py),anciennePositionX(px), anciennePositionY(py),
      points_vie(pv), force(f), rapidite(r)
{
}

// Destructeur
Entite::~Entite()
{
}

// Méthodes
bool Entite::estVivant() const
{
    return points_vie > 0;
}

void Entite::MAJPV(int points)
{
    points_vie += points;
    if (points_vie < 0)
        points_vie = 0;
}
void Entite::MAJArgent(int montant)
{
    somme_argent += montant;
    if (somme_argent < 0) somme_argent = 0; // on évite l'argent négatif
    cout << nom << " a maintenant " << somme_argent << " pièces.\n";
}


// Accesseurs
std::string Entite::GetNom() const { return nom; }
int Entite::GetArgent() const { return somme_argent; }
int Entite::GetPositionX() const { return positionX; }
int Entite::GetPositionY() const { return positionY; }
int Entite::GetPV() const { return points_vie; }
int Entite::GetForce() const { return force; }
void Entite::setPosition(int x, int y)
{
    anciennePositionX = positionX;
    anciennePositionY = positionY;
    positionX = x;
    positionY = y;
}

void Entite::revenirCasePrecedente()
{
    positionX = anciennePositionX;
    positionY = anciennePositionY;
}
