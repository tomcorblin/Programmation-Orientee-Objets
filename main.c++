#include "Ennemi.h"
#include "Personnage.h"
#include "Objet.h"
#include "Plateau.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>

using namespace std;



// Générer une race aléatoire
Ennemi::Race randomRace()
{
    int r = randomInt(0, 5); // 6 races possibles
    return static_cast<Ennemi::Race>(r);
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    // Création du plateau
    Plateau plateau;

    // Choix du joueur
    ClassePersonnage classeChoisie = Personnage::choisirClasse();
    Personnage joueur("Joueur", classeChoisie, 0, 0);
    plateau.placerPersonnage(&joueur, 0, 0);

    // Création et Placement du marchand
    Marchand marchand("Le Marchand", 5, 5);
    plateau.placerMarchand(&marchand, 5, 5);


    // Création des objets
    vector<Objet> objets = {
        Objet("Seringue de dopamine", TypeObjet::Seringue_de_steroid, 15),
        Objet("Robot Chirurgien", TypeObjet::Robot_Chirurgien, 20)
    };

    // Placement aléatoire des objets
    for (auto& obj : objets)
    {
        int x, y;
        do {
            x = rand() % LARGEUR;
            y = rand() % HAUTEUR;
        } while (!plateau.placerObjet(&obj, x, y));
    }

    // Création et placement de 5 ennemis aléatoires
    vector<Ennemi> ennemis;
    const int N_ENNEMIS = 5;
    for (int i = 0; i < N_ENNEMIS; ++i) {
        // Choix aléatoire de la race
        Ennemi::Race r = static_cast<Ennemi::Race>(randomInt(0, 5)); // 0 à 5 = toutes les races

        // Création de l'ennemi avec nom aléatoire, les stats seront définies dans le constructeur
        ennemis.emplace_back(Ennemi::NomRace(r), r, 0, 0);

        // Placement aléatoire sur le plateau
        int x, y;
        do {
            x = randomInt(0, LARGEUR-1);
            y = randomInt(0, HAUTEUR-1);
        } while (!plateau.placerEnnemi(&ennemis.back(), x, y));
    }

    // Boucle de jeu
    string commande;
    while (true)
    {
        plateau.afficher();

        cout << endl << "(z,s,q,d) deplacement | i inventaire | u utiliser objet | x quitter : ";
        cin >> commande;

        if (commande == "x")
            break;

        if (commande == "i")
        {
            joueur.afficherInventaire();
            continue;
        }

        if (commande == "u")
        {
            joueur.afficherInventaire();
            if (!joueur.GetInventaire().empty())
            {
                int choix;
                cout << "Quel objet utiliser ? ";
                cin >> choix;
                bool fin = (joueur.GetInventaire()[choix]->GetType()== TypeObjet::PortalGun );
                joueur.utiliserObjet(choix);
                if (fin) plateau.lancerFinDuJeu(&joueur);
                
                
            }
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
