#include "Plateau.h"
#include "Ennemi.h"

// Constructeur : initialise toutes les cases à nullptr
Plateau::Plateau()
{
    for (int y = 0; y < HAUTEUR; y++)
        for (int x = 0; x < LARGEUR; x++)
        {
            plateau[y][x].perso = nullptr;
            plateau[y][x].objet = nullptr;
            plateau[y][x].ennemi = nullptr;
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
            else if (plateau[y][x].ennemi) std::cout << "E ";
            else if (plateau[y][x].marchand) std::cout << "M ";
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

                // Combat si case avec ennemi
                if (plateau[ny][nx].ennemi != nullptr)
                {
                	Ennemi* e = plateau[ny][nx].ennemi;
                	lancerCombat(p, e);
                	// Si l'ennemi est mort après combat, on libère la case
                	if (!e->estVivant()) plateau[ny][nx].ennemi = nullptr;
                	return true;
                }
                // Interaction si case avec marchand
                if (plateau[ny][nx].marchand != nullptr)
                {
                    Marchand* m = plateau[ny][nx].marchand;

                    // Fonction qui gère tout le dialogue et les achats
                    lancerInteractionMarchand(p, m);

                    // Après interaction, on ne modifie pas la case : le marchand reste là
                    return true;
                }
                else
                {
                	// déplacer le personnage
                	plateau[ny][nx].perso = p;
                	plateau[y][x].perso = nullptr;
                }
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
    if (plateau[y][x].objet != nullptr || plateau[y][x].perso != nullptr) return false; // case déjà occupée par un objet
    plateau[y][x].objet = o;
    return true;
}

bool Plateau::placerEnnemi(Ennemi* e, int x, int y) {
    if (x < 0 || x >= LARGEUR || y < 0 || y >= HAUTEUR) return false;
    if (plateau[y][x].perso != nullptr || plateau[y][x].ennemi != nullptr) return false; // case occupée
    plateau[y][x].ennemi = e;
    e->setPosition(x, y); // mettre à jour la position de l'ennemi
    return true;
}

void Plateau::lancerCombat(Personnage* joueur, Ennemi* ennemi)
{
    std::cout << "Combat engagé avec " << ennemi->GetNom()
              << " (PV: " << ennemi->GetPV() << ") !" << std::endl;

    std::string choix;
    while (joueur->estVivant() && ennemi->estVivant())
    {
        std::cout << "\nActions possibles : (a)ttaque | (i)nventaire | (u)tiliser objet | (f)uir\nChoix : ";
        std::cin >> choix;

        if (choix == "i")
        {
            joueur->afficherInventaire();
        }
        else if (choix == "u")
        {
            joueur->afficherInventaire();
            if (!joueur->GetInventaire().empty())
            {
                int index;
                std::cout << "Quel objet utiliser ? ";
                std::cin >> index;
                joueur->utiliserObjet(index);
            }
        }
        else if (choix == "a") // Attaque
        {
            std::cout << joueur->GetNom() << " attaque " << ennemi->GetNom()
                      << " et inflige " << joueur->GetForce() << " points de dégât !" << std::endl;
            ennemi->MAJPV(-joueur->GetForce());

            if (!ennemi->estVivant())
            {
                std::cout << ennemi->GetNom() << " est vaincu !" << std::endl;
                // Récompense en argent
                int gain = ennemi->GetArgent();
                std::cout << "Vous récupérez " << gain << " pièces !" << std::endl;
                joueur->ajouterArgent(gain);
                break;
            }

            // Contre-attaque de l'ennemi
            std::cout << ennemi->GetNom() << " attaque en retour et inflige "
                      << ennemi->GetForce() << " points de dégâts !" << std::endl;
            joueur->MAJPV(-ennemi->GetForce());
            if (!joueur->estVivant())
            {
                std::cout << "Vous êtes mort ! Fin du jeu." << std::endl;
                exit(0);
            }
            cout << "Vos PV : " << joueur->GetPV()<< endl;
            cout << "PV de l'ennemi : " << ennemi->GetPV()<< endl;
        }
        else if (choix == "f") // Fuir
        {
            int chance = joueur->GetChance();
            int tirage = randomInt(1, 100);
            if (tirage <= chance)
            {
                std::cout << "Vous réussissez à fuir et revenez à la case précédente !" << std::endl;
                joueur->revenirCasePrecedente();
                break;
            }
            else
            {
                std::cout << "Fuite échouée !" << std::endl;
                // Ennemi attaque si échec
                std::cout << ennemi->GetNom() << " attaque et inflige " << ennemi->GetForce() << " points de dégâts !" << std::endl;
                joueur->MAJPV(-ennemi->GetForce());
                if (!joueur->estVivant())
                {
                    std::cout << "Vous êtes mort ! Fin du jeu." << std::endl;
                    exit(0);
                }
                cout << "Vos PV : " << joueur->GetPV()<< endl;
            }
        }
    }
}

bool Plateau::placerMarchand(Marchand* m, int x, int y)
{
    if (x < 0 || x >= LARGEUR || y < 0 || y >= HAUTEUR) return false;
    if (plateau[y][x].perso || plateau[y][x].ennemi || plateau[y][x].objet || plateau[y][x].marchand)
        return false; // case occupée
    plateau[y][x].marchand = m;
    return true;
}

void Plateau::lancerInteractionMarchand(Personnage* p, Marchand* m)
{
    bool enInteraction = true;

    while (enInteraction)
    {
        std::cout << "\nVous êtes face au marchand !" << std::endl;
        m->parler();
        std::cout << "Choisissez un objet à acheter (-1 pour partir) : ";
        int choix;
        std::cin >> choix;

        if (choix == -1)
        {
            enInteraction = false;
            std::cout << "Vous quittez le marchand.\n";
        }
        else
        {
            m->vendreObjet(choix, *p);
        }
    }
}

