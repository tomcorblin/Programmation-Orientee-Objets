#include "Personnage.h"
#include <iostream>

// Constructeur
Personnage::Personnage(std::string nom, ClassePersonnage c, int px, int py)
    : Entite(nom, 0, px, py, 0, 0, 0), classe(c), chance(0)
{
    // Initialisation des statistiques selon la classe
    switch (classe)
    {
    case ClassePersonnage::Rick:
        points_vie = 80; force = 15; rapidite = 10; chance = 12; break;

    case ClassePersonnage::Morty:
        points_vie = 60; force = 8; rapidite = 16; chance = 20; break;

    case ClassePersonnage::Summer:
        points_vie = 90; force = 12; rapidite = 12; chance = 10; break;

    case ClassePersonnage::Beth:
        points_vie = 100; force = 18; rapidite = 8; chance = 12; break;

    case ClassePersonnage::Jerry:
        points_vie = 50; force = 6; rapidite = 10; chance = 25; break;

    case ClassePersonnage::MrBoiteACaca:
        points_vie = 70; force = 5; rapidite = 4; chance = 5; break;
    }
}

// Accesseurs
ClassePersonnage Personnage::GetClasse() const
{
    return classe;
}

int Personnage::GetChance() const
{
    return chance;
}

const vector<Objet*>& Personnage::GetInventaire() const
{
	return inventaire;
}
// Ajouter un objet à l’inventaire
void Personnage::ajouterObjet(Objet* o)
{
    if (o != nullptr)
        inventaire.push_back(o);
}

// Affichage
void Personnage::afficher() const
{
    std::string icone;
    switch (classe)
    {
    case ClassePersonnage::Rick: icone = "🧪"; break;
    case ClassePersonnage::Morty: icone = "👦"; break;
    case ClassePersonnage::Summer: icone = "👧"; break;
    case ClassePersonnage::Beth: icone = "👩"; break;
    case ClassePersonnage::Jerry: icone = "👨"; break;
    case ClassePersonnage::MrBoiteACaca: icone = "💩"; break;
    }

    std::cout << "Personnage : " << nom << " " << icone << std::endl;
    std::cout << "PV : " << points_vie << std::endl;
    std::cout << "Force : " << force << std::endl;
    std::cout << "Rapidite : " << rapidite << std::endl;
    std::cout << "Chance : " << chance << std::endl;

    if (!inventaire.empty())
        {
            std::cout << "Inventaire :" << std::endl;
            for (const auto& obj : inventaire)
                std::cout << " - " << obj->GetNom() << std::endl;
        }
}

void Personnage::afficherInventaire() const
{
    if (inventaire.empty())
    {
        std::cout << "Inventaire vide.\n";
        return;
    }

    std::cout << "Inventaire :\n";
    for (size_t i = 0; i < inventaire.size(); ++i)
    {
        std::cout << i << " - " << inventaire[i]->GetNom() << "\n";
    }
}

void Personnage::utiliserObjet(int index)
{
    if (index < 0 || index >= inventaire.size())
    {
        std::cout << "Objet invalide.\n";
        return;
    }

    inventaire[index]->utiliser(*this);

    // Optionnel : supprimer l’objet après usage
    inventaire.erase(inventaire.begin() + index);
}

