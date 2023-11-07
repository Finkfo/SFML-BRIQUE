#include "GameObject.h"

GameObject::GameObject(float x, float y, float speedX, float speedY, float width, float height, sf::Color color)
{
	this->x = x;
	this->y = y;
	this->speedX = speedX;
	this->speedY = speedY;
	this->width = width;
	this->height = height;
	this->color = color;
	
	graphic = new sf::RectangleShape(sf::Vector2f(width, height));
	graphic->setPosition(x, y);
	graphic->setFillColor(color);


}

GameObject::GameObject(float x, float y, float speedX, float speedY, float size, sf::Color color)
{
	this->x = x;
	this->y = y;
	this->speedX = speedX;
	this->speedY = speedY;
	this->size = size;
	this->color = color;

	graphic = new sf::CircleShape(size);
	graphic->setPosition(x, y);
	graphic->setFillColor(color);
}

GameObject::~GameObject()
{

}

sf::Shape* GameObject::GetRender()
{
	return graphic;
}

void GameObject::setRotation(float angle)
{
	orientation = angle;
	graphic->setRotation(angle);
}

void GameObject::Rotate(float angle, float fDeltaTime)
{
	orientation += fDeltaTime * angle;
	graphic->setRotation(orientation);
}

void GameObject::Move(float fDeltaTime)
{
	x += fDeltaTime * speedX;
	y += fDeltaTime * speedY;
	graphic->setPosition(x, y);
}

