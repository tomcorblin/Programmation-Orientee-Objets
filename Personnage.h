#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include "Entite.h"
#include "Objet.h"
#include <vector>
#include <string>
using namespace std;

// Enum pour toutes les classes/personnages
enum class ClassePersonnage
{
    Rick,
    Morty,
    Summer,
    Beth,
    Jerry,
    MrBoiteACaca  // valeur de l'énum, OK ici
};

class Personnage : public Entite
{
private:
    ClassePersonnage classe;  // <-- c'est la variable
    int chance;
    vector<Objet*> inventaire; // <- inventaire des objets

public:
    // Constructeur
    Personnage(std::string nom, ClassePersonnage c, int px, int py);

    // Accesseurs
    ClassePersonnage GetClasse() const;
    int GetChance() const;
    const vector<Objet*>& GetInventaire() const;

    // Méthodes
    void afficher() const;
    void ajouterObjet(Objet* o);
    void afficherInventaire() const;
    void utiliserObjet(int index);
    void augmenterForce(int f);
    void ajouterArgent(int a);

};

#endif
