#ifndef ENTITE_H

#define ENTITE_H

#include <string>

class Entite

{
protected:
 std::string nom;
 int somme_argent;
 int positionX;
 int positionY;
 int points_vie;
 int force;
 int rapidite;



public:

 // Constructeur
 Entite(std::string n, int sa, int px, int py, int pv, int f, int r);

 // Destructeur
 virtual ~Entite();

 // Méthodes
 bool estVivant() const;
 void MAJPV(int points);



 // Accesseurs
 std::string GetNom() const;
 int GetArgent() const;
 int GetPositionX() const;
 int GetPositionY() const;
 int GetPV() const;
 int GetForce() const;
 int GetRapidite() const;
};



#endif
