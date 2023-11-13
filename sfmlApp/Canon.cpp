#include "Canon.h"

Canon::Canon(const GameObject::RectDesc desc) : GameObject(desc)
{
}

Canon::~Canon() {
}

void Canon::Follow(sf::Vector2i window) {
	sf::Vector2i mouse = sf::Mouse::getPosition()-window;
	sf::Vector2f canon = GetPosition();
	sf::Vector2f mouseVect = { mouse.x - canon.x,mouse.y - canon.y };
	sf::Vector2f xVect = { 1,0 };
	//std::cout << mouse.x << "; " << mouse.y << std::endl;


	float angle = acos(Scalaire(mouseVect, xVect)/(Module(mouseVect)*Module(xVect)));
	/* +90 pour que l'origine soit en haut
	* -1 pour que le sens de rotation soit cohérent entre sens trigo et sens
	* de rotation en c++ qui est lesens horaira
	* /M_PI/180 pour passé de radians à degrés
	*/
	angle = 90+(- 1 * (angle / (M_PI / 180)));



	if (mouse.y < canon.y) {
		GameObject::SetRotation(angle);
	}
}
/*Calcul angle canon = angle entre vecteur x(1,0) et vecteur souris = (xsouris-xcanon,ysouris-ycanon)
* angle entre vecteur = acos(<u°v>/(module(u)*module(v)))
*/