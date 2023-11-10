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

<<<<<<< Updated upstream
=======
//changer le nom car pas assez comprehensible ou alors placer contenu dans SetRotation
void GameObject::HorizontalBounce() {
	SetRotation(180 - orientation);

}
void GameObject::VerticalBounce() {
	SetRotation(0 - orientation);
}

void GameObject::Reset()
{
	graphic->setPosition(origineX, origineY);
}

void GameObject::CollisionWindow(sf::Vector2f screen)
{
	bool firstCollision = false;
	sf::Vector2f position = graphic->getPosition();
	float radius = this->width;


	if (position.x - radius <= 0 || position.x + radius >= screen.x) {
		while (position.x - radius <= 0 || position.x + radius >= screen.x)
		{
			if (firstCollision) {
				break;
			}
			firstCollision = true;
			VerticalBounce();
			position = graphic->getPosition();
		}
	}

	if (position.y - radius <= 0 || position.y + radius >= screen.y ) {
		while (position.y - radius <= 0 || position.y + radius >= screen.x) 
		{
			if (firstCollision) {
				break;
			}
			firstCollision = true;
			HorizontalBounce();
			position = graphic->getPosition();
		}
	}
}

void GameObject::CollisionObject(GameObject& other) {
	sf::Vector2f distance = other.graphic->getPosition() - graphic->getPosition();
	float radius = this->width;

	// Calculer la somme des demi-largeurs et demi-hauteurs
	float combinedHalfWidth = (radius + other.width) / 2.0f;
	float combinedHalfHeight = (radius + other.height) / 2.0f;

	// Calculer la différence absolue entre les centres
	float offsetX = std::abs(distance.x) - combinedHalfWidth;
	float offsetY = std::abs(distance.y) - combinedHalfHeight;

	// Vérifier s'il y a collision
	if (offsetX < 0 && offsetY < 0) {

		if (offsetX > offsetY) {
			// Collision selon l'axe x
			if (distance.x > 0) {
				std::cout << "Collision sur la gauche" << std::endl;
				VerticalBounce();
			}
			else {
				std::cout << "Collision sur la droite" << std::endl;
				VerticalBounce();
			}
		}
		else {
			// Collision selon l'axe y
			if (distance.y > 0) {
				std::cout << "Collision en haut" << std::endl;
				HorizontalBounce();
			}
			else {
				std::cout << "Collision en bas" << std::endl;
				HorizontalBounce();
			}
		}
	}
}
>>>>>>> Stashed changes
