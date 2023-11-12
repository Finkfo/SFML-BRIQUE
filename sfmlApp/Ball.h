#pragma once
#include "GameObject.h"

class Ball : public GameObject
{

public:
	Ball(const GameObject::CircleDesc desc);
	~Ball();

};
sf::Vector2f PositionCalcul(float angle, sf::Vector2f origine, sf::Vector2f size);