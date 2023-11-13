#include "Brick.h"

Brick::Brick(const GameObject::RectDesc desc, int life) : GameObject(desc)
{
	this->life = life;
}

Brick::~Brick(){
}

void Brick::LostLife() {
		life = life - 1;
		std::cout << "Be hit; " << life << std::endl;
	if (life <= 0) {
		std::cout << "dead" << std::endl;
	}
}

bool Brick::IsDead() {
	bool isDead = false;
	if (life <= 0) {
		isDead = true;
	}
	return isDead;
}

