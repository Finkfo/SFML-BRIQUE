#include "Raquette.h"
Raquette::Raquette(const GameObject::RectDesc desc) : GameObject(desc)
{
}

Raquette::~Raquette() {
}

void Raquette::RaquetteFollow() {
	GameObject::SetPosition(sf::Mouse::getPosition());
}