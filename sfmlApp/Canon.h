#pragma once
#include "GameObject.h"
#include "Math.h"

class Canon : public GameObject
{

public:
	Canon(const GameObject::RectDesc desc);
	~Canon();

	void Follow(sf::Vector2i);

};