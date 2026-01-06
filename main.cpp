#include "Ennemi.hpp"
#include <iostream>
#include <ctime>

using namespace std;

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
}








