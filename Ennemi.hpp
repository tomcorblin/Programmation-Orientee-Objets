
#ifndef ENNEMI_HPP_
#define ENNEMI_HPP_
#include <string>
#include "Entite.hpp"
#include <random>
#include <vector>


class Ennemi : public Entite
{
public :
	enum class Race
	{
		snake, alien, humanoid, robot, dragon, insect,
	};
    struct Stats {
            int pv;
            int force;
            int rapidite;
            int argent;
        };
    static const std::vector<std::string> nomsAlien = {
        "Tony l'usurpateur de WC", "Glootie le cupidon moderne", "L'oncle Steve qui a la classe",
		"Unity l'ex de Rick", "Magma-Q le rappeur qui crache des flammes", "Keara la chasseuse de Jerry",
		"Fart, être gazeux inter-dimensionnel", "Madame refrigerateur", "L'hamster dans des fesses"
    };
    static const std::vector<std::string> nomsSnake = {
		"Le serpent journaliste", "Le serpent préhistorique", "Le serpent des annees 80", "Le serpent des services secrets",
		"Le serpent avec des jambes", "Le serpent soldat", "Le serpent linguiste", "Le serpent Lincoln","Le serpent Hitler",
		"Slippy le serpent", "Le serpent cyborg"
    };
    static const std::vector<std::string> nomsHumanoid = {
		"L'homme double micro-onde", "Hologramme de Rick", "Le Fauteuil-Personne","La Pizza-Personne","Morty toxique",
		"Morty avec une trompe", "Morty Jr le brutal", "Mr. NeedFul le diabolique",
		"Pichael Thompson Le jumeau de Michael Thompson", "Rick aquatique (il a un bocal avec un poisson a la place de la tete)",
		"Mr. Nimbus le pervers"
    };
    static const std::vector<std::string> nomsRobots = {
		"Le serpent terminator", "randotron le générateur d'aleatoire",
		"heistotron le générateur d'histoire de braquage deja vu", "Rick Robot","Morty Robot", "Cyborg Photogaphe",
		"Gwendolyn le robot de reproduction", "Robot à couper le beurre", "Digestibot", "Les restes d'anciens robots"
    };
    static const std::vector<std::string> nomsDragon = {
		"Balthromaw le pervers grincheux", "Shadow Jacker le vieux pervers", "Michael, un des dragons pervers",
		"Debrah la dragonne nonne",
    };
    static const std::vector<std::string> nomsInsects = {
		"Jerry en guepe", "Beth en guepe", "La larve de Mr.GoldenFold", "Mr.GoldenFold en chenille",
		"Morty en crevette fasciste", "Le clone de Rick en crevette fasciste", "un million de fourmis", "Gromflomite n°45924",
		"Vermigurber la grosse mouche"
    };
private:
    Race race;
    std::string action;



public :
    //Constructeur
    Ennemi(std::string n, Race r,
            int px, int py);

    // Accesseur
    Race GetRace();
    std::string GetAction(Race race);

    //Méthodes
    static Stats StatsRace(Race race);
    static std::string NomRace(Race race);
};



#endif /* ENNEMI_HPP_ */
