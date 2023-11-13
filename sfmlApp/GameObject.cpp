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
	this->wasCollidingLastFrame = false;


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
	this->wasCollidingLastFrame = false;

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
	std::cout << "bounce" << std::endl;
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

	if (position.y - radius <= 0) {
		firstCollision = true;
		HorizontalBounce();
		position = graphic->getPosition();
	}
}

bool GameObject::CollisionObject(GameObject& other) {
	bool collide = false;

	sf::Vector2f distance = other.graphic->getPosition() - graphic->getPosition();
	float radius = this->width;

	// Calculer la somme des demi-largeurs et demi-hauteurs
	float combinedHalfWidth = (radius + other.width) / 2.0f;
	float combinedHalfHeight = (radius + other.height) / 2.0f;

	// Calculer la différence absolue entre les centres
	float offsetX = std::abs(distance.x) - combinedHalfWidth;
	float offsetY = std::abs(distance.y) - combinedHalfHeight;

	// Vérifier s'il y a collision

	if (CheckCollisions(other)) {
		collide = true;
	/*if (offsetX < 0 && offsetY < 0) {*/

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
	return collide;
}

bool GameObject::CheckCollisions(const GameObject& goOther) {
	bool firstCollision=false;
	// Vérifier si les AABB sont en collision
	bool isColliding = CheckAABBCollision(this, &goOther);

	// Si en collision
	if (isColliding) {
		if (!wasCollidingLastFrame) {
			firstCollision = true;
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
	return firstCollision;
}

// Méthode pour vérifier la collision entre deux AABB
bool GameObject::CheckAABBCollision(const GameObject* go1, const GameObject* go2) {
	// Obtenir les positions et dimensions des GameObjects
	sf::Vector2f pos1 = go1->graphic->getPosition();
	sf::Vector2f pos2 = go2->graphic->getPosition();
	float width1 = go1->width;
	float height1 = go1->height;
	float width2 = go2->width;
	float height2 = go2->height;

	// Calculer les bornes des GameObjects
	float left1 = pos1.x - width1 / 2;
	float right1 = pos1.x + width1 / 2;
	float top1 = pos1.y - height1 / 2;
	float bottom1 = pos1.y + height1 / 2;

	float left2 = pos2.x - width2 / 2;
	float right2 = pos2.x + width2 / 2;
	float top2 = pos2.y - height2 / 2;
	float bottom2 = pos2.y + height2 / 2;

	// Vérifier si les AABB se chevauchent sur les deux axes
	return (left1 < right2 && right1 > left2 && top1 < bottom2 && bottom1 > top2);
}

// Méthodes virtuelles à implémenter dans les classes filles
void GameObject::OnCollisionEnter() {
	std::cout << "Entrer en collision" << std::endl;
	// Logique pour lorsqu'une collision commence
}

void GameObject::OnCollisionStay() {
	std::cout << " Toujours en collision" << std::endl;
	// Logique pour lorsqu'une collision persiste
}

void GameObject::OnCollisionExit() {
	std::cout << "Sortir de la collision" << std::endl;
	// Logique pour lorsqu'une collision se termine
}