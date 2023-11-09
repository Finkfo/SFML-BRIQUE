#include "GameObject.h"$



GameObject::GameObject(float x, float y, float width, float height,float orientation, float speed, float angularSpeed, sf::Color color)
{
	this->origineX = x;
	this->origineY = y;
	this->width = width;
	this->height = height;
	this->orientation = orientation;
	this->speed = speed;
	this->angularSpeed = angularSpeed;
	this->color = color;


	graphic = new sf::RectangleShape(sf::Vector2f(width, height));
	graphic->setOrigin(0.5 * width, 0.5 * height);
	//std::cout << graphic->getOrigin().x << "; " << graphic->getOrigin().y << std::endl;
	graphic->setPosition(x, y);
	graphic->setFillColor(color);
	SetRotation(orientation);

}

GameObject::GameObject(float x, float y, float size, float orientation, float speed, float angularSpeed, sf::Color color){

	this->origineX = x;
	this->origineY = y;
	this->width = size / 2;
	this->height = size / 2;
	this->orientation = orientation;
	this->speed = speed;
	this->angularSpeed = angularSpeed;
	this->color = color;

	graphic = new sf::CircleShape(width);
	graphic->setOrigin(width, height);
	//std::cout << graphic->getOrigin().x << "; " << graphic->getOrigin().y << std::endl;
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
	sf::Vector2f oPosition = graphic->getPosition();

	oPosition.x = oPosition.x + direction.x * deltaTime * speed;
	oPosition.y = oPosition.y + direction.y * deltaTime * speed;

	graphic->setPosition(oPosition);
}

void GameObject::Rotate(float deltaTime)
{
	orientation += deltaTime * angularSpeed;
	graphic->setRotation(orientation);
}

void GameObject::SetRotation(float angle/*, float fRatioX = 1 / 2.f, float fRatioY = 1 / 2.f*/)
{
	//graphic->setOrigin(fRatioX * width, fRatioY * height);

	orientation = angle;
	graphic->setRotation(angle);
	direction.x = std::sin(orientation * (M_PI / 180));
	direction.y = -1 * std::cos(orientation * (M_PI / 180));
	std::cout << direction.x << "; " << direction.y << std::endl;
}

//changer le nom car pas assez comprehensible ou alors placer contenu dans SetRotation
void GameObject::HorizontalBounce() {
	SetRotation(180 - orientation);

}
void GameObject::VerticaltBounce() {
	SetRotation(0 - orientation);
}

void GameObject::Reset()
{
	graphic->setPosition(origineX, origineY);
}