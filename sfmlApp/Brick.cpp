#include "Brick.h"

Brick::Brick(const GameObject::RectDesc& oDesc, int life) : GameObject(oDesc)
{
	this->life = life;
}

Brick::~Brick(){
}