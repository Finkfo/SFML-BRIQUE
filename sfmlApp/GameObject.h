#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define _USE_MATH_DEFINES

class GameObject
{

private:

	bool wasCollidingLastFrame;

	float origineX;
	float origineY;

	float width;
	float height;

	float ancrageX;
	float ancrageY;

	float speed;
	float angularSpeed;

	float orientation = 0;

	sf::Vector2f direction = { 0,0 };

	sf::Color color;
	sf::Shape* graphic;

	std::string collisionDir;
	std::string collisionFace;
	std::string lastFace;


public:

	typedef struct RectDesc
	{
		float origineX;
		float origineY;
		float width;
		float height;
		float ancrageX = width / 2;
		float ancrageY = height / 2;
		float orientation = 0;
		float speed = 0;
		float angularSpeed = 0;
		sf::Color color = sf::Color::Red;
	};

	typedef struct CircleDesc
	{
		float origineX;
		float origineY;
		float radius;
		float ancrageX = radius / 2;
		float ancrageY = radius / 2;
		float orientation = 0;
		float speed = 0;
		float angularSpeed = 0;
		sf::Color color = sf::Color::Blue;
	};
	GameObject(RectDesc desc);
	GameObject(CircleDesc desc);
	~GameObject();

	sf::Shape* GetRender();

	

	void Update(float deltaTime);
	void Move(float deltaTime);
	void Rotate(float deltaTime);
	void SetRotation(float angle);
	void HorizontalBounce();
	void VerticalBounce();
	sf::Vector2f GetPosition();
	float GetOrientation();
	sf::Vector2f GetSize();
	void Reset();

	void CollisionWindow(sf::Vector2f screen);
	
	bool CheckCollisions(const GameObject& goOther);
	bool CheckOBBCollision(const GameObject* other);

	virtual void OnCollisionEnter();
	virtual void OnCollisionStay();
	virtual void OnCollisionExit();

	void SetPosition(sf::Vector2i position);

};

/*Calcul angle canon = angle entre vecteur x(1,0) et vecteur souris = (xsouris-xcanon,ysouris-ycanon)
* angle entre vecteur = acos(<u°v>/(module(u)*module(v)))
*/