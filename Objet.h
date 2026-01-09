#ifndef OBJET_H
#define OBJET_H

#include <string>
#include <iostream>

class Personnage;

enum class TypeObjet
{
    Seringue_de_dopamine,       // augmente la force
    Potion,      // Potion de soin
    Argent,      // Argent à récupérer
    PortalGun
};

class Objet
{
private:
    std::string nom;
    TypeObjet type;
    int valeur; // pour soin, force, bouclier ou argent

public:
    // Constructeur
    Objet(std::string n, TypeObjet t, int v);

    // Accesseurs
    std::string GetNom() const;
    TypeObjet GetType() const;
    int GetValeur() const;

    // Méthodes
    void utiliser(Personnage& joueur); // On pourra redéfinir plus tard selon le type
};

#endif
