#include "Ennemi.hpp"

using namespace std;

// Génération d'aléatoire
int randomInt(int min, int max) {
    static std::random_device rd;  // graine aléatoire
    static std::mt19937 gen(rd()); // moteur Mersenne Twister
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

// Accesseur
Ennemi::Race Ennemi::GetRace() {return race;}

// Chaque race a une phrase spéciale quand il attaque
std::string Ennemi::GetAction(Race race)
{
	switch(race)
	{
	case Race::alien:
		return "Vomit un liquide verdâtre acide en gesticulant";
	case Race::dragon:
		return "Crache du feu de manière nonchalente";
	case Race::humanoid:
		return "Met une claque de toute ses forces en gémissant";
	case Race::insect:
		return "Se faufile dans tes vêtements et te chatouille fortement";
	case Race::robot:
		return "émet un flash aveuglant et t'assène un coup de tête dévastateur";
	case Race::snake:
		return "te mords sans surprise";
	}
	return " ";
}

// On donne des stats prédéfinis aux ennemie selon leur race. L'argent est généré aléatoirement, dans une plage qui corresponds à l'ennemi
Ennemi::Stats Ennemi::StatsRace(Race race)
{
	switch(race)
	{
	case Race::alien :
		return {20,15,30,randomInt(15,100)};
	case Race::dragon :
		return {50,40,15,randomInt(150,500)};
	case Race::humanoid :
		return {15,5,20,randomInt(2,10)};
	case Race::insect :
		return {5,20,40,randomInt(10,50)};
	case Race ::robot:
		return {40,45,20,randomInt(150,500)};
	case Race ::snake:
		return {10,40,40,randomInt(10,70)};
	}
	return {0,0,0,0};
}
//Constructeur
Ennemi::Ennemi(std::string n, Ennemi::Race r,
        int px, int py)
     : Entite(n, 0, px, py, 0, 0, 0), race(r)
{
	Stats s=StatsRace(r);
	points_vie=s.pv;
	force=s.force;
	rapidite=s.rapidite;
	somme_argent=s.argent;
}

// Générateur de nom
std::string Ennemi::NomRace(Ennemi::Race r)
{
	switch(r)
	{
	case Race::alien:

	}
}






