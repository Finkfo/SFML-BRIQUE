#pragma once
#include "GameObject.h"

class Ball : public GameObject
{

public:
	Ball(const GameObject::CircleDesc desc);
	~Ball();

};