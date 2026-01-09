#include "Plateau.h"

// Constructeur : initialise toutes les cases à nullptr
Plateau::Plateau()
{
    for (int y = 0; y < HAUTEUR; y++)
        for (int x = 0; x < LARGEUR; x++)
        {
            plateau[y][x].perso = nullptr;
            plateau[y][x].objet = nullptr;
        }

    std::srand(std::time(nullptr)); // initialisation du générateur aléatoire
}

// Affichage ASCII du plateau
void Plateau::afficher() const
{
    for (int y = 0; y < HAUTEUR; y++)
    {
        for (int x = 0; x < LARGEUR; x++)
        {
            if (plateau[y][x].perso) std::cout << "P ";
            else if (plateau[y][x].objet) std::cout << "O ";
            else std::cout << ". ";
        }
        std::cout << std::endl;
    }
}

// Place un personnage à une position donnée
bool Plateau::placerPersonnage(Personnage* p, int x, int y)
{
    if (x < 0 || x >= LARGEUR || y < 0 || y >= HAUTEUR) return false;
    if (plateau[y][x].perso != nullptr) return false; // case occupée

    plateau[y][x].perso = p;
    return true;
}

// Déplacer un personnage de dx/dy
bool Plateau::deplacerPersonnage(Personnage* p, int dx, int dy)
{
    for (int y = 0; y < HAUTEUR; y++)
    {
        for (int x = 0; x < LARGEUR; x++)
        {
            if (plateau[y][x].perso == p)
            {
                int nx = x + dx;
                int ny = y + dy;

                if (nx < 0 || nx >= LARGEUR || ny < 0 || ny >= HAUTEUR) return false;
                if (plateau[ny][nx].perso != nullptr) return false; // case occupée

                // ramasser objet si présent
                if (plateau[ny][nx].objet)
                {
                    p->ajouterObjet(plateau[ny][nx].objet);
                    std::cout << p->GetNom() << " ramasse " << plateau[ny][nx].objet->GetNom() << std::endl;
                    plateau[ny][nx].objet = nullptr;
                }

                // déplacer le personnage
                plateau[ny][nx].perso = p;
                plateau[y][x].perso = nullptr;
                return true;
            }
        }
    }
    return false; // personnage non trouvé
}

// Placer un objet à une position donnée
bool Plateau::placerObjet(Objet* o, int x, int y)
{
    if (x < 0 || x >= LARGEUR || y < 0 || y >= HAUTEUR) return false;
    if (plateau[y][x].objet != nullptr) return false; // case déjà occupée par un objet
    plateau[y][x].objet = o;
    return true;
}
