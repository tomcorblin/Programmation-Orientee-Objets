#ifndef MARCHAND_H
#define MARCHAND_H

#include "Personnage.h"
#include "Objet.h"
#include <vector>
#include <string>
#include <iostream>
#include "Entite.h"

class Marchand : public Entite
{
private:
    std::vector<Objet> stock;

public:
    Marchand(const std::string& n, int x, int y);

    //Méthodes
    void parler();
    void vendreObjet(int index, Personnage& joueur);

    //Accesseurs
    const std::vector<Objet>& getStock() const { return stock; }
    const std::string& getNom() const { return nom; }
    int getX() const { return positionX; }
    int getY() const { return positionY; }
};

#endif
