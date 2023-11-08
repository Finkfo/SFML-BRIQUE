#include "GameObject.h"

GameObject::GameObject(float x, float y, float width, float height,float orientation, float speed, float angularSpeed, sf::Color color)
{
	this->x = x-width/2;
	this->y = y-height/2;
	this->origineX = x;
	this->origineY = y;
	this->speed = speed;
	this->angularSpeed = angularSpeed;
	this->width = width;
	this->height = height;
	this->orientation = orientation;
	this->color = color;


	graphic = new sf::RectangleShape(sf::Vector2f(width, height));
	graphic->setPosition(x, y);
	graphic->setFillColor(color);
	SetRotation(orientation);

}

GameObject::GameObject(float x, float y, float size, float orientation, float speed, float angularSpeed, sf::Color color){
	this->x = x - size;
	this->y = y - size;
	this->origineX = x;
	this->origineY = y;
	this->speed = speed;
	this->angularSpeed = angularSpeed;
	this->size = size;
	this->orientation = orientation;
	this->color = color;

	graphic = new sf::CircleShape(size);
	graphic->setPosition(x, y);
	graphic->setFillColor(color);
	SetRotation(orientation);
}

GameObject::~GameObject()
{

}

sf::Shape* GameObject::GetRender()
{
	return graphic;
}

void GameObject::Move(float deltaTime)
{
	x += direction[0] * deltaTime * speed;
	y += direction[1] * deltaTime * speed;
	graphic->setPosition(x, y);
}

void GameObject::Rotate(float deltaTime)
{
	orientation += deltaTime * angularSpeed;
	graphic->setRotation(orientation);
}

void GameObject::SetRotation(float angle, float fRatioX = 1/2.f, float fRatioY = 1/2.f)
{

	graphic->setOrigin(fRatioX * width, fRatioY * height);

	orientation = angle;
	graphic->setRotation(angle);
	direction[0] = std::sin(orientation * (M_PI / 180));
	direction[1] = -1 * std::cos(orientation * (M_PI / 180));
	std::cout << direction[0] << "; " << direction[1] << std::endl;
}

void GameObject::Reset()
{
	x = origineX;
	y = origineY;
}

//changer le nom car pas assez comprehensible ou alors placer contenu dans SetRotation
void GameObject::dirVect() {
	
}