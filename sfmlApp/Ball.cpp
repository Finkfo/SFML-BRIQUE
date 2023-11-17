#include "Ball.h"

Ball::Ball(const GameObject::CircleDesc desc) : GameObject(desc)
{
}

Ball::~Ball() {
}


bool Ball::CheckOutbounds(sf::Vector2f position, sf::Vector2f screen) {
	bool out = false;

	if (position.x < 0 || position.x > screen.x || position.y < 0 || position.y > screen.y) {
		out = true;
	}

	return out;
}

sf::Vector2f PositionCalcul(float angle, sf::Vector2f origine, sf::Vector2f size) {
	sf::Vector2f position;
	position.x = origine.x+size.y*(std::sin(angle * (M_PI / 180)));
	position.y = origine.y+size.y*(-1 * std::cos(angle * (M_PI / 180)));
	return position;
}