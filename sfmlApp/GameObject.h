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
public:

	typedef struct RectDesc
	{
		float x;
		float y;
		float w;
		float h;
		float orientation = 0;
		float speed = 0;
		float angularSpeed = 0;
		sf::Color color = sf::Color::Red;
	};

	typedef struct CircleDesc 
	{
		float x;
		float y;
		float r;
	};

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

	//std::vector<int> a = { (0,0,0) };
	GameObject(float x, float y, float width, float height, float orientation, float speed, float angularSpeed = 0, sf::Color color = sf::Color::Red);
	GameObject(float x, float y, float size, float orientation, float speed, float angularSpeed = 0, sf::Color color = sf::Color::Blue);
public:

	typedef struct CircleDesc
	{
		float x = 0;
		float y = 0;
		float r;
	};

	typedef struct RectDesc
	{
		float x;
		float y;
		float w;
		float h;
	};

	~GameObject();

	sf::Shape* GetRender();

	

	void Move(float deltaTime);
	void Rotate(float deltaTime);
	void SetRotation(float angle);
	void HorizontalBounce();
	void VerticaltBounce();
	void Reset();
};

/*Calcul angle canon = angle entre vecteur x(1,0) et vecteur souris = (xsouris-xcanon,ysouris-ycanon)
* angle entre vecteur = acos(<u°v>/(module(u)*module(v)))
*/