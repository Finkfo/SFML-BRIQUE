#include "GameObject.h"

GameObject::GameObject(float x, float y, float speedX, float speedY, int width, int height, sf::Color color)
{
	this->x = x;
	this->y = y;
	this->speedX = speedX;
	this->speedY = speedY;
	this->width = width;
	this->height = height;
	this->color = color;
	graphic.setPosition(x, y);
	graphic.setSize(sf::Vector2f(width, height));
	graphic.setFillColor(color);

}

GameObject::~GameObject()
{

}

sf::RectangleShape GameObject::GetRender()
{
	return graphic;
}

void GameObject::Move()
{
	x += speedX;
	y += speedY;
	graphic.setPosition(x, y);
}