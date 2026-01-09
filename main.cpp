#include "Ennemi.hpp"
#include <iostream>
#include <ctime>
#include "Entite.h"
#include "Personnage.h"
#include "Objet.h"
#include "Plateau.h"
#include <string>

using namespace std;

// -------------------------------
// Choix de la classe du joueur
// -------------------------------
ClassePersonnage choisirClasse()
{
    int choix = -1;
    char confirmation = 'n';

    while (confirmation != 'o')
    {
        cout << "Choisissez votre personnage :" << endl;
        cout << "1 - Rick" << endl;
        cout << "2 - Morty" << endl;
        cout << "3 - Summer" << endl;
        cout << "4 - Beth" << endl;
        cout << "5 - Jerry" << endl;
        cout << "6 - Mr Boite a Caca" << endl;

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

        // Création temporaire pour afficher les stats
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

// -------------------------------
// Main
// -------------------------------
int main()
{
	srand(static_cast<unsigned int>(time(nullptr))); // initialise le générateur
	// Création d'un ennemi de chaque race
	Ennemi e1("Zorg", Ennemi::Race::alien, 0, 0);
	Ennemi e2("Drako", Ennemi::Race::dragon, 1, 2);
	Ennemi e3("Gnomey", Ennemi::Race::humanoid, 5, 3);
	Ennemi e4("Insecto", Ennemi::Race::insect, 2, 4);
	Ennemi e5("Robo", Ennemi::Race::robot, 3, 1);

	Ennemi::Stats s;


    // Pour e1
    s = Ennemi::StatsRace(Ennemi::Race::dragon); // On peut utiliser la fonction statique
    std::cout << "Ennemi " << "Zorg"
              << " | PV: " << s.pv
              << " | Force: " << s.force
              << " | Rapidite: " << s.rapidite
              << " | Argent: " << s.argent
              << std::endl;



	//////////////////////////debut jeu ///////////////////////
	srand(time(nullptr));

    // 1️⃣ Choix du personnage
    ClassePersonnage classeChoisie = choisirClasse();
    Personnage joueur("Joueur", classeChoisie, 0, 0);

    // 2️⃣ Création du plateau
    Plateau plateau;
    plateau.placerPersonnage(&joueur, 0, 0);

    // 3️⃣ Création des objets
    vector<Objet> objets = {
        Objet("PortalGun", TypeObjet::PortalGun, 0),
        Objet("Seringue de dopamine", TypeObjet::Seringue_de_dopamine, 15),
        Objet("Potion", TypeObjet::Potion, 20)
    };

    // 4️⃣ Placement aléatoire des objets
    for (auto& obj : objets)
    {
        int x, y;
        do
        {
            x = rand() % LARGEUR;
            y = rand() % HAUTEUR;
        } while (!plateau.placerObjet(&obj, x, y));
    }

    // 5️⃣ Boucle de jeu
    string commande;
    while (true)
    {
        plateau.afficher();

        if (commande == "u")
        {
            joueur.afficherInventaire();
            if (!joueur.GetInventaire().empty())
            {
                int choix;
                cout << "Quel objet utiliser ? ";
                cin >> choix;
                joueur.utiliserObjet(choix);
            }
            continue;
        }

        cout << "(z,s,q,d) deplacement | i inventaire | x quitter : ";
        cin >> commande;

        if (commande == "x")
            break;

        if (commande == "i")
        {
            const auto& inv = joueur.GetInventaire();
            cout << "Inventaire du joueur :" << endl;

            if (inv.empty())
                cout << " - vide" << endl;

            for (const auto& obj : inv)
                cout << " - " << obj->GetNom() << endl;

            continue;
        }

        int dx = 0, dy = 0;
        if (commande == "z") dy = -1;
        else if (commande == "s") dy = 1;
        else if (commande == "q") dx = -1;
        else if (commande == "d") dx = 1;

        if (!plateau.deplacerPersonnage(&joueur, dx, dy))
            cout << "Deplacement impossible !" << endl;
    }

    cout << "Fin du jeu." << endl;
    return 0;
}








