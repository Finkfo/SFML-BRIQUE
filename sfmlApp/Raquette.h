#pragma once
#include "GameObject.h"
#include "Math.h"

class Raquette : public GameObject
{

public:
	Raquette(const GameObject::RectDesc desc);
	~Raquette();

	void RaquetteFollow(sf::Vector2i screen);

};