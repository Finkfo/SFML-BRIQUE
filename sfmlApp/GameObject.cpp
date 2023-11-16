#include "GameObject.h"



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
	graphic->setOutlineThickness(2);
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

void GameObject::HorizontalBounce() {
	SetRotation(180 - orientation);
}

void GameObject::VerticalBounce() {
	SetRotation(0 - orientation);
}

sf::Vector2f GameObject::GetPosition() {
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

	if (position.y - radius <= 0 ) {
		firstCollision = true;
		HorizontalBounce();
		position = graphic->getPosition();
	}
}

bool GameObject::CheckCollisions(const GameObject& goOther) {

	bool isColliding = CheckOBBCollision(&goOther);

	// Si en collision
	if (isColliding) {
		if (!wasCollidingLastFrame) {
			OnCollisionEnter();
		}
		else {
			OnCollisionStay();
		}
		wasCollidingLastFrame = isColliding;
		return true;
	}
	// S'il n'y a pas de collision
	else {
		if (wasCollidingLastFrame) {
			OnCollisionExit();
			wasCollidingLastFrame = isColliding;
			return false;
		}
	}
}

bool GameObject::CheckRaquetteCollision(const GameObject& goOther) {
	bool isColliding = CheckOBBRaquetteCollision(&goOther);

	// Si en collision
	if (isColliding) {
		if (!wasCollidingLastFrame) {
			OnCollisionEnter();
		}
		else {
			OnCollisionStay();
		}
		wasCollidingLastFrame = isColliding;
		return 1;
	}
	// S'il n'y a pas de collision
	else {
		if (wasCollidingLastFrame) {
			OnCollisionExit();
			wasCollidingLastFrame = isColliding;
			return 0;
		}
	}
}
bool GameObject::CheckOBBRaquetteCollision(const GameObject* other) {
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
		// Déterminer la face spécifique de la collision
		if (std::abs(distanceX) > std::abs(distanceY)) {
			// Collision plus proche sur l'axe vertical
			if (distanceX > 0) {
				std::cout << this->GetPosition().x << "; "<< other->graphic->getPosition().x << std::endl;
				this->collisionFace = "Gauche";
				this->collisionDir = "Vertical";
			}
			else {
				std::cout << this->GetPosition().x << "; " << other->graphic->getPosition().x << std::endl;
				this->collisionFace = "Droite";
				this->collisionDir = "Vertical";
			}
		}
		else {
			// Collision plus proche sur l'axe horizontal
			if (distanceY > 0) {
				this->collisionFace = "Haut";
				this->collisionDir = "Horizontal";
			}
			else {
				float angle = (ballCenter.x - brickCenter.x)*75/90;
				this->SetRotation(angle);
				this->collisionFace = "Bas";
				this->collisionDir = "Horizontal";
			}
		}
		// Collision détectée
		return true;
	}
	else {
		// Pas de collision
		this->collisionDir = "None";
		return false;
	}
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
		// Déterminer la face spécifique de la collision
		if (std::abs(distanceX) > std::abs(distanceY)) {
			// Collision plus proche sur l'axe vertical
			if (distanceX > 0) {
				this->collisionFace = "Gauche";
				this->collisionDir = "Vertical";
			}
			else {
				this->collisionFace = "Droite";
				this->collisionDir = "Vertical";
			}
		}
		else {
			// Collision plus proche sur l'axe horizontal
			if (distanceY > 0) {
				this->collisionFace = "Haut";
				this->collisionDir = "Horizontal";
			}
			else {
				this->collisionFace = "Bas";
				this->collisionDir = "Horizontal";
			}
		}
		// Collision détectée
		return true;
	}
	else {
		// Pas de collision
		this->collisionDir = "None";
		return false;
	}
}

// Méthodes virtuelles à implémenter dans les classes filles
void GameObject::OnCollisionEnter() {
	std::cout << "Entrer en collision" << std::endl;
	

	if (this->collisionDir == "Vertical" && this->lastFace != this->collisionFace ) {
		VerticalBounce();
		this->lastFace = this->collisionFace;
	}
	else if (this->collisionDir == "Horizontal" && this->lastFace != this->collisionFace) {
		HorizontalBounce();
		this->lastFace = this->collisionFace;
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



void GameObject::SetPosition(sf::Vector2i position){
	graphic->setPosition(position.x, position.y);
}