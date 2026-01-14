#include "Ennemi.h"
#include "Personnage.h"
#include "Objet.h"
#include "Plateau.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>

using namespace std;

// Fonction pour choisir une classe
ClassePersonnage choisirClasse()
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

// Générer une race aléatoire
Ennemi::Race randomRace()
{
    int r = randomInt(0, 5); // 6 races possibles
    return static_cast<Ennemi::Race>(r);
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    // 1️⃣ Création du plateau
    Plateau plateau;

    // 2️⃣ Choix du joueur
    ClassePersonnage classeChoisie = choisirClasse();
    Personnage joueur("Joueur", classeChoisie, 0, 0);
    plateau.placerPersonnage(&joueur, 0, 0);

    // Création et Placement du marchand
    Marchand marchand("Le Marchand", 5, 5);
    plateau.placerMarchand(&marchand, 5, 5);


    // 3️⃣ Création des objets
    vector<Objet> objets = {
        Objet("Seringue de dopamine", TypeObjet::Seringue_de_dopamine, 15),
        Objet("Potion", TypeObjet::Potion, 20)
    };

    // 4️⃣ Placement aléatoire des objets
    for (auto& obj : objets)
    {
        int x, y;
        do {
            x = rand() % LARGEUR;
            y = rand() % HAUTEUR;
        } while (!plateau.placerObjet(&obj, x, y));
    }

    // 5️⃣ Création et placement de 5 ennemis aléatoires
    vector<Ennemi> ennemis;
    const int N_ENNEMIS = 5;
    for (int i = 0; i < N_ENNEMIS; ++i) {
        // Choix aléatoire de la race
        Ennemi::Race r = static_cast<Ennemi::Race>(randomInt(0, 5)); // 0 à 5 = toutes les races

        // Création de l'ennemi avec nom générique, les stats seront définies dans le constructeur
        ennemis.emplace_back("Ennemi" + std::to_string(i+1), r, 0, 0);

        // Placement aléatoire sur le plateau
        int x, y;
        do {
            x = randomInt(0, LARGEUR-1);
            y = randomInt(0, HAUTEUR-1);
        } while (!plateau.placerEnnemi(&ennemis.back(), x, y));
    }

    // 6️⃣ Boucle de jeu
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
                joueur.utiliserObjet(choix);
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

        //si le joueur est sur la case du marchand
        Case* caseJoueur = plateau.getCase(joueur.GetPositionX(), joueur.GetPositionY());
        if (caseJoueur->marchand)
        {
            Marchand* m = caseJoueur->marchand;
            cout << "\nVous rencontrez " << m->getNom() << " !" << endl;

            string cmd;
            while (true)
            {
                cout << "\nOptions : a acheter | x quitter le marchand : ";
                cin >> cmd;

                if (cmd == "x")
                {
                    cout << "Vous quittez le marchand." << endl;
                    break;
                }
                else if (cmd == "a")
                {
                    cout << "Stock disponible :" << endl;
                    for (size_t i = 0; i < m->getStock().size(); ++i)
                        cout << i << " - " << m->getStock()[i].GetNom() << endl;

                    int choix;
                    cout << "Quel objet acheter ? ";
                    cin >> choix;

                    m->vendreObjet(choix, joueur);
                }
            }

            continue; // le joueur ne peut rien faire d'autre tant qu'il est sur la case du marchand
        }
    }

    cout << "Fin du jeu." << endl;
    return 0;
}
