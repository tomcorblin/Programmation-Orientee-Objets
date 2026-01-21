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

    std::cout << "________________________________________"<<endl;
    std::cout << "Personnage : " << nom << " " << icone << std::endl;
    std::cout << "PV : " << points_vie << std::endl;
    std::cout << "Force : " << force << std::endl;
    std::cout << "Rapidite : " << rapidite << std::endl;
    std::cout << "Chance : " << chance << std::endl;
    std::cout << "________________________________________"<<endl;

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

    std::cout << endl<< "Inventaire :\n";
    for (size_t i = 0; i < inventaire.size(); ++i)
    {
        std::cout << i << " - " << inventaire[i]->GetNom() << "\n";
    }
    std::cout << endl;
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
    if (inventaire[index]->GetType()!=TypeObjet::PortalGun) inventaire.erase(inventaire.begin() + index);
}

void Personnage::augmenterForce(int f)
{
	force += f;
}
void Personnage::augmenterRapidite(int r)
{
	rapidite += r;
}
void Personnage::ajouterArgent(int a)
{
	somme_argent += a;
}


// Fonction pour choisir une classe
ClassePersonnage Personnage::choisirClasse()
{
    int choix = -1;
    char confirmation = 'n';

    while (confirmation != 'o')
    {
        cout << "Choisissez votre personnage :" << endl;
        cout << "1 - Rick\n2 - Morty\n3 - Summer\n4 - Beth\n5 - Jerry\n6 - Mr Boite a Caca\n";
        cout << "Votre choix : ";
        cin >> choix;

        ClassePersonnage classe;
        switch (choix)
        {
        case 1: classe = ClassePersonnage::Rick; break;
        case 2: classe = ClassePersonnage::Morty; break;
        case 3: classe = ClassePersonnage::Summer; break;
        case 4: classe = ClassePersonnage::Beth; break;
        case 5: classe = ClassePersonnage::Jerry; break;
        case 6: classe = ClassePersonnage::MrBoiteACaca; break;
        default: continue;
        }

        Personnage temp("Aperçu", classe, 0, 0);
        cout << "\nStatistiques du personnage :" << endl;
        temp.afficher();

        cout << "\nConfirmer ce choix ? (o/n) : ";
        cin >> confirmation;
        cout << endl;
    }

    switch (choix)
    {
    case 1: return ClassePersonnage::Rick;
    case 2: return ClassePersonnage::Morty;
    case 3: return ClassePersonnage::Summer;
    case 4: return ClassePersonnage::Beth;
    case 5: return ClassePersonnage::Jerry;
    case 6: return ClassePersonnage::MrBoiteACaca;
    default: return ClassePersonnage::Morty;
    }
}
