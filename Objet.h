#ifndef OBJET_H
#define OBJET_H

#include <string>
#include <iostream>

class Personnage;

enum class TypeObjet
{
    Seringue_de_steroid,       // augmente la force
    Chaussures_qui_courent_vite,
    Robot_Chirurgien,      // Potion de soin
    Argent,      // Argent à récupérer
    PortalGun // Pour fin du jeu
};

class Objet
{
private:
    std::string nom;
    TypeObjet type;
    int valeur; // pour soin, force, bouclier ou argent
    int prix;

public:
    // Constructeur
    Objet(std::string n, TypeObjet t, int v, int p);

    // Accesseurs
    std::string GetNom() const;
    TypeObjet GetType() const;
    int GetValeur() const;
    int GetPrix() const;

    // Méthodes
    void utiliser(Personnage& joueur); // On pourra redéfinir plus tard selon le type 

};

#endif
