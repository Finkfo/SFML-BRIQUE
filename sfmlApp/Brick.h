#pragma once
#include "GameObject.h"

class Brick : public GameObject
{
private:
	int life;

public:
	Brick(const GameObject::RectDesc desc, int life);
	~Brick();

	void LostLife();

};