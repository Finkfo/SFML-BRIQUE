#include "GameObject.h"

//GameObject::GameObject() {
//	this->origineX = 0;
//	this->origineY = 0;
//	this->width = 0;
//	this->height = 0;
//	this->orientation = 0;
//	this->speed = 0;
//	this->angularSpeed = 0;
//	this->color = sf::Color::Green;
//}

GameObject::GameObject(RectDesc desc)
{
	this->origineX = desc.origineX;
	this->origineY = desc.origineY;
	this->width = desc.width;
	this->height = desc.height;
	this->ancrageX = desc.ancrageX;
	this->ancrageY = desc.ancrageY;
	this->orientation = desc.orientation;
	this->speed = desc.speed;
	this->angularSpeed = desc.angularSpeed;
	this->color = desc.color;


	graphic = new sf::RectangleShape(sf::Vector2f(width, height));
	graphic->setOrigin(ancrageX, ancrageY);
	//std::cout << graphic->getOrigin().x << "; " << graphic->getOrigin().y << std::endl;
	graphic->setPosition(origineX, origineY);
	graphic->setFillColor(color);
	graphic->setOutlineThickness(4);
	graphic->setOutlineColor(sf::Color::Black);
	SetRotation(orientation);

}

GameObject::GameObject(CircleDesc desc){

	this->origineX = desc.origineX;
	this->origineY = desc.origineY;
	this->width = desc.radius / 2;
	this->height = desc.radius / 2;
	this->ancrageX = desc.ancrageX;
	this->ancrageY = desc.ancrageY;
	this->orientation = desc.orientation;
	this->speed = desc.speed;
	this->angularSpeed = desc.angularSpeed;
	this->color = desc.color;

	graphic = new sf::CircleShape(width);
	graphic->setOrigin(ancrageX, ancrageY);
	//std::cout << graphic->getOrigin().x << "; " << graphic->getOrigin().y << std::endl;
	graphic->setPosition(origineX, origineY);
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

void GameObject::Update(float deltaTime) {
	Move(deltaTime);
	Rotate(deltaTime);

}

void GameObject::Move(float deltaTime)
{
	sf::Vector2f Position = graphic->getPosition();

	Position.x = Position.x + direction.x * deltaTime * speed;
	Position.y = Position.y + direction.y * deltaTime * speed;

	graphic->setPosition(Position);
}

void GameObject::Rotate(float deltaTime)
{
	orientation += deltaTime * angularSpeed;
	graphic->setRotation(orientation);
}

void GameObject::SetRotation(float angle)
{
	//graphic->setOrigin(fRatioX * width, fRatioY * height);

	orientation = angle;
	graphic->setRotation(angle);
	direction.x = std::sin(orientation * (M_PI / 180));
	direction.y = -1 * std::cos(orientation * (M_PI / 180));
	//std::cout << direction.x << "; " << direction.y << std::endl;
}

//changer le nom car pas assez comprehensible ou alors placer contenu dans SetRotation
void GameObject::HorizontalBounce() {
	SetRotation(180 - orientation);

}
void GameObject::VerticalBounce() {
	SetRotation(0 - orientation);
}

sf::Vector2f GameObject::GetPosition(){
	sf::Vector2f position = graphic->getPosition();
	return position;
}
float GameObject::GetOrientation() {
	float orientation = this->orientation;
	return orientation;
}
sf::Vector2f GameObject::GetSize() {
	sf::Vector2f size = { width,height };
	return size;
}

void GameObject::Reset()
{
	graphic->setPosition(origineX, origineY);
}