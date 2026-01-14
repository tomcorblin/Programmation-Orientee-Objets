#ifndef MARCHAND_H
#define MARCHAND_H

#include "Personnage.h"
#include "Objet.h"
#include <vector>
#include <string>
#include <iostream>

class Marchand
{
private:
    std::string nom;
    int posX;
    int posY;
    std::vector<Objet> stock;

public:
    Marchand(const std::string& n, int x, int y);

    //Méthodes
    void parler();
    void vendreObjet(int index, Personnage& joueur);

    //Accesseurs
    const std::vector<Objet>& getStock() const { return stock; }
    const std::string& getNom() const { return nom; }
    int getX() const { return posX; }
    int getY() const { return posY; }
};

#endif
