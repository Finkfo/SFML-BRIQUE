#include "GameObject.h"

GameObject::GameObject(float x, float y, float width, float height, float orientation, float speed, float angularSpeed, sf::Color color)
{
	this->origineX = x;
	this->origineY = y;
	this->width = width;
	this->height = height;
	this->orientation = orientation;
	this->speed = speed;
	this->angularSpeed = angularSpeed;
	this->color = color;
	this->wasCollidingLastFrame = false;


	graphic = new sf::RectangleShape(sf::Vector2f(width, height));
	graphic->setOrigin(0.5 * width, 0.5 * height);
	//std::cout << graphic->getOrigin().x << "; " << graphic->getOrigin().y << std::endl;
	graphic->setPosition(x, y);
	graphic->setFillColor(color);
	SetRotation(orientation);

}

GameObject::GameObject(float x, float y, float diameter, float orientation, float speed, float angularSpeed, sf::Color color) {

	this->origineX = x;
	this->origineY = y;
	this->width = diameter / 2;
	this->height = diameter / 2;
	this->orientation = orientation;
	this->speed = speed;
	this->angularSpeed = angularSpeed;
	this->color = color;
	this->wasCollidingLastFrame = false;

	graphic = new sf::CircleShape(width);
	hitboxGraphic =  sf::RectangleShape(sf::Vector2f(width, height));
	graphic->setOrigin(width, height);
	/*hitboxGraphic->setOrigin(width, height);*/
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
	float x = graphic->getPosition().x + direction.x * deltaTime * speed;
	float y = graphic->getPosition().y + direction.y * deltaTime * speed;

	graphic->setPosition(x, y);
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

void GameObject::Reset()
{
	graphic->setPosition(origineX, origineY);
}

void GameObject::HorizontalBounce() {
	SetRotation(180 - orientation);

}

void GameObject::VerticalBounce() {
	SetRotation(0 - orientation);
}

void GameObject::CollisionWindow(sf::Vector2f screen)
{
	bool firstCollision = false;
	sf::Vector2f position = graphic->getPosition();
	float radius = this->width;


	if (position.x - radius <= 0 || position.x + radius >= screen.x) {
			firstCollision = true;
			VerticalBounce();
			position = graphic->getPosition();
	}

	if (position.y - radius <= 0 || position.y + radius >= screen.y ) {
			firstCollision = true;
			HorizontalBounce();
			position = graphic->getPosition();
	}
}



void GameObject::CheckCollisions(const GameObject& goOther) {
	// Vérifier si les AABB sont en collision
	bool isColliding = CheckOBBCollision(&goOther);

	// Si en collision
	if (isColliding) {
		if (!wasCollidingLastFrame) {
			OnCollisionEnter();
		}
		else {
			OnCollisionStay();
		}
	}
	// S'il n'y a pas de collision
	else {
		if (wasCollidingLastFrame) {
			OnCollisionExit();
		}
	}

	// Mise à jour de l'état de collision pour le prochain tour de boucle
	wasCollidingLastFrame = isColliding;

}

bool GameObject::CheckOBBCollision(const GameObject* other) {
	sf::Vector2f ballCenter = this->graphic->getPosition();
	float ballRadius = this->width;

	sf::Vector2f brickCenter = other->graphic->getPosition();
	float brickHalfWidth = other->width / 2;
	float brickHalfHeight = other->height / 2;

	// Trouve le point le plus proche sur le rectangle de la brique au centre de la balle
	float closestX = std::max(brickCenter.x - brickHalfWidth, std::min(ballCenter.x, brickCenter.x + brickHalfWidth));
	float closestY = std::max(brickCenter.y - brickHalfHeight, std::min(ballCenter.y, brickCenter.y + brickHalfHeight));

	// Calculer la distance entre ce point et le centre de la balle
	float distanceX = ballCenter.x - closestX;
	float distanceY = ballCenter.y - closestY;

	// Si la distance est inférieure au rayon de la balle il y a une collision
	if ((distanceX * distanceX + distanceY * distanceY) < (ballRadius * ballRadius)) {


		// Déterminer la direction de rebond
		if (std::abs(distanceX) > std::abs(distanceY)) {

			// Collision principalement sur l'axe Vertical
			this ->collisionDir = "Vertical";
		}
		else {

			// Collision principalement sur l'axe Horizontal
			this ->collisionDir = "Horizontal";
		}
		// Collision détectée
		return true;

	}
	else {
		// Pas de collision
		return false;
		this ->collisionDir = "None";
	}
}

// Méthodes virtuelles à implémenter dans les classes filles
void GameObject::OnCollisionEnter() {
	std::cout  << "Entrer en collision" << std::endl;
	if (this->collisionDir == "Vertical") {
			VerticalBounce();
		}
	else if (this->collisionDir == "Horizontal") {
			HorizontalBounce();
		}
	 
}

void GameObject::OnCollisionStay() {
	std::cout << " Toujours en collision" << std::endl;
	// Logique pour lorsqu'une collision persiste
}

void GameObject::OnCollisionExit() {
	std::cout << "Sortir de la collision" << std::endl;
	// Logique pour lorsqu'une collision se termine
}
