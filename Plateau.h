#ifndef PLATEAU_H
#define PLATEAU_H

#include "Personnage.h"
#include "Objet.h"
#include "Marchand.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int LARGEUR = 10;
const int HAUTEUR = 10;

class Ennemi;

struct Case
{
    Personnage* perso;
    Objet* objet;
    Ennemi* ennemi;
    Marchand* marchand = nullptr;
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
    bool placerEnnemi(Ennemi* e, int x, int y);
    bool placerObjet(Objet* o, int x, int y);
    bool placerMarchand(Marchand* m, int x, int y);
    void lancerCombat(Personnage* joueur, Ennemi* ennemi);
    void lancerInteractionMarchand(Personnage* p, Marchand* m);
    void lancerFinDuJeu(Personnage* p);

    Case* getCase(int x, int y) { return &plateau[y][x]; }
};

#endif
