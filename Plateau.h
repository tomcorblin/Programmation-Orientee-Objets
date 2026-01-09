#ifndef PLATEAU_H
#define PLATEAU_H

#include "Personnage.h"
#include "Objet.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int LARGEUR = 10;
const int HAUTEUR = 10;

struct Case
{
    Personnage* perso; // nullptr si pas de personnage
    Objet* objet;      // nullptr si pas d'objet
    // Ennemi* ennemi;  // à ajouter plus tard
};

class Plateau
{
private:
    Case plateau[HAUTEUR][LARGEUR];

public:
    Plateau();

    void afficher() const;

    bool placerPersonnage(Personnage* p, int x, int y);
    bool deplacerPersonnage(Personnage* p, int dx, int dy);

    bool placerObjet(Objet* o, int x, int y);
};

#endif
