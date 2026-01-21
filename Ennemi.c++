#include "Ennemi.h"
#include <iostream>
#include <random>

// Définition des vecteurs statiques
const std::vector<std::string> Ennemi::nomsAlien = {
    "Tony l'usurpateur de WC", "Glootie le cupidon moderne", "L'oncle Steve qui a la classe",
    "Unity l'ex de Rick", "Magma-Q le rappeur qui crache des flammes", "Keara la chasseuse de Jerry",
    "Fart, être gazeux inter-dimensionnel", "Madame refrigerateur", "L'hamster dans des fesses"
};

const std::vector<std::string> Ennemi::nomsSnake = {
    "Le serpent journaliste", "Le serpent préhistorique", "Le serpent des annees 80", "Le serpent des services secrets",
    "Le serpent avec des jambes", "Le serpent soldat", "Le serpent linguiste", "Le serpent Lincoln","Le serpent Hitler",
    "Slippy le serpent", "Le serpent cyborg"
};

const std::vector<std::string> Ennemi::nomsHumanoid = {
    "L'homme double micro-onde", "Hologramme de Rick", "Le Fauteuil-Personne","La Pizza-Personne","Morty toxique",
    "Morty avec une trompe", "Morty Jr le brutal", "Mr. NeedFul le diabolique",
    "Pichael Thompson Le jumeau de Michael Thompson", "Rick aquatique (il a un bocal avec un poisson a la place de la tete)",
    "Mr. Nimbus le pervers"
};

const std::vector<std::string> Ennemi::nomsRobots = {
    "Le serpent terminator", "randotron le générateur d'aleatoire",
    "heistotron le générateur d'histoire de braquage deja vu", "Rick Robot","Morty Robot", "Cyborg Photogaphe",
    "Gwendolyn le robot de reproduction", "Robot à couper le beurre", "Digestibot", "Les restes d'anciens robots"
};

const std::vector<std::string> Ennemi::nomsDragon = {
    "Balthromaw le pervers grincheux", "Shadow Jacker le vieux pervers", "Michael, un des dragons pervers",
    "Debrah la dragonne nonne"
};

const std::vector<std::string> Ennemi::nomsInsects = {
    "Jerry en guepe", "Beth en guepe", "La larve de Mr.GoldenFold", "Mr.GoldenFold en chenille",
    "Morty en crevette fasciste", "Le clone de Rick en crevette fasciste", "un million de fourmis", "Gromflomite n°45924",
    "Vermigurber la grosse mouche"
};

// Génération aléatoire
int randomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

// Constructeur avec coordonnées
Ennemi::Ennemi(std::string n, Race r, int px, int py)
    : Entite(n, 0, px, py, 0, 0, 0), race(r)
{
    Stats s = StatsRace(r);
    points_vie = s.pv;
    force = s.force;
    rapidite = s.rapidite;
    somme_argent = s.argent;
}

// Accesseur
Ennemi::Race Ennemi::GetRace() const { return race; }

// Phrase d’action
std::string Ennemi::GetAction(Race race) const
{
    switch (race)
    {
        case Race::alien: return "Vomit un liquide verdatre acide en gesticulant";
        case Race::dragon: return "Crache du feu de manière nonchalente";
        case Race::humanoid: return "Met une claque de toute ses forces en gémissant";
        case Race::insect: return "Se faufile dans tes vêtements et te chatouille fortement";
        case Race::robot: return "émet un flash aveuglant et t'assène un coup de tête dévastateur";
        case Race::snake: return "te mords sans surprise";
        default: return "Action inconnue";
    }
}

// Stats par race
Ennemi::Stats Ennemi::StatsRace(Race race)
{
    switch (race)
    {
        case Race::alien: return {20,15,30,randomInt(15,100)};
        case Race::dragon: return {50,40,15,randomInt(150,500)};
        case Race::humanoid: return {15,5,20,randomInt(2,10)};
        case Race::insect: return {5,20,40,randomInt(10,50)};
        case Race::robot: return {40,45,20,randomInt(150,500)};
        case Race::snake: return {10,40,40,randomInt(10,70)};
        default: return {0,0,0,0};
    }
}

// Nom aléatoire par race
std::string Ennemi::NomRace(Race r)
{
    const std::vector<std::string>* noms = nullptr;

    switch(r)
    {
        case Race::alien: noms = &nomsAlien; break;
        case Race::dragon: noms = &nomsDragon; break;
        case Race::humanoid: noms = &nomsHumanoid; break;
        case Race::insect: noms = &nomsInsects; break;
        case Race::robot: noms = &nomsRobots; break;
        case Race::snake: noms = &nomsSnake; break;
    }

    if (noms && !noms->empty())
        return (*noms)[randomInt(0, noms->size() - 1)];

    return "Ennemi inconnu";
}

//Afficheur race
std::string Ennemi::RaceToString(Race r)
{
    switch(r)
    {
        case Race::alien:return "Alien";
        case Race::dragon:return "Dragon";
        case Race::humanoid:return "Humanoide";
        case Race::insect:return "Insecte";
        case Race::robot:return "Robot";
        case Race::snake:return "Serpent";
        default:return "Inconnu";
    }
}

