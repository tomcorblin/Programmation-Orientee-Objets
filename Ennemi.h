#ifndef ENNEMI_HPP_
#define ENNEMI_HPP_

#include <string>
#include <vector>
#include <random>
#include "Entite.h"

class Ennemi : public Entite
{
public:
    enum class Race { snake, alien, humanoid, robot, dragon, insect };

    struct Stats {
        int pv;
        int force;
        int rapidite;
        int argent;
    };

private:
    Race race;
    std::string action;

public:
    // Constructeur
    Ennemi(std::string n, Race r, int px, int py);

    // Accesseur
    Race GetRace() const;
    std::string GetAction(Race race) const;

    // Méthodes
    static Stats StatsRace(Race race);
    static std::string NomRace(Race race);

    // Noms par race
    static const std::vector<std::string> nomsAlien;
    static const std::vector<std::string> nomsSnake;
    static const std::vector<std::string> nomsHumanoid;
    static const std::vector<std::string> nomsRobots;
    static const std::vector<std::string> nomsDragon;
    static const std::vector<std::string> nomsInsects;
};

int randomInt(int min, int max);

#endif
