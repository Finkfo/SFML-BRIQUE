#include "Raquette.h"
Raquette::Raquette(const GameObject::RectDesc desc) : GameObject(desc)
{
}

Raquette::~Raquette() {
}

void Raquette::RaquetteFollow(sf::Vector2i screen) {
	sf::Vector2i mouse = sf::Mouse::getPosition() - screen;
	int x = mouse.x<75?75:mouse.x>1205?1205:mouse.x;
	GameObject::SetPosition({ x,700 });
}