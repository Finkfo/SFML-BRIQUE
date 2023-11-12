#include "Ball.h"

Ball::Ball(const GameObject::CircleDesc desc) : GameObject(desc)
{
}

Ball::~Ball() {
}

sf::Vector2f PositionCalcul(float angle, sf::Vector2f origine, sf::Vector2f size) {
	sf::Vector2f position;
	position.x = origine.x+size.y*(std::sin(angle * (M_PI / 180)));
	position.y = origine.y+size.y*(-1 * std::cos(angle * (M_PI / 180)));
	return position;
}