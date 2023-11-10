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

	float origineX;
	float origineY;

	float width;
	float height;
	float speed;
	float angularSpeed;

	float orientation = 0;

	sf::Vector2f direction = { 0,0 };

	sf::Color color;
	sf::Shape* graphic;

	//std::vector<int> a = { (0,0,0) };public:


public:

	typedef struct RectDesc
	{
		float x;
		float y;
		float width;
		float height;
		float orientation = 0;
		float speed = 0;
		float angularSpeed = 0;
		sf::Color color = sf::Color::Red;
	};

	typedef struct CircleDesc
	{
		float x;
		float y;
		float radius;
		float orientation = 0;
		float speed = 0;
		float angularSpeed = 0;
		sf::Color color = sf::Color::Blue;
	};
	//GameObject();
	GameObject(RectDesc desc);
	GameObject(CircleDesc desc);
	~GameObject();

	sf::Shape* GetRender();

	

	void Move(float deltaTime);
	void Rotate(float deltaTime);
	void SetRotation(float angle);
	void HorizontalBounce();
	void VerticalBounce();
	void Reset();
};

/*Calcul angle canon = angle entre vecteur x(1,0) et vecteur souris = (xsouris-xcanon,ysouris-ycanon)
* angle entre vecteur = acos(<u°v>/(module(u)*module(v)))
*/