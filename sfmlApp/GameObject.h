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
	float speed;
	float angularSpeed;

	float orientation = 0;

	sf::Vector2f direction = { 0,0 };
	//std::vector<float> direction = { 0,0 };

	sf::Color color;
	sf::Shape* graphic;


public:
	GameObject(float x, float y, float width, float height, float orientation, float speed, float angularSpeed, sf::Color color);
	GameObject(float x, float y, float size, float orientation, float speed, float angularSpeed, sf::Color color);
	~GameObject();

	sf::Shape* GetRender();



	void Move(float deltaTime);
	void Rotate(float deltaTime);
	void SetRotation(float angle);
	void HorizontalBounce();
	void VerticalBounce();
	void Reset();
	void CollisionWindow(sf::Vector2f screen);
	//void CollisionObject(GameObject& other);
	void CheckCollisions(const GameObject& goOther);

	virtual void OnCollisionEnter();
	virtual void OnCollisionStay();
	virtual void OnCollisionExit();

	bool CheckAABBCollision(const GameObject* go1, const GameObject* go2);

};

/*Calcul angle canon = angle entre vecteur x(1,0) et vecteur souris = (xsouris-xcanon,ysouris-ycanon)
* angle entre vecteur = acos(<u°v>/(module(u)*module(v)))
*/

