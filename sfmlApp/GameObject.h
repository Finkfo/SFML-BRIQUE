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
	float x;
	float y;

	float origineX;
	float origineY;

	float width;
	float height;
	float size;

	float speed;
	float angularSpeed;

	float orientation = 0;

	std::vector<float> direction = { 0,0 };

	sf::Color color;
	sf::Shape* graphic;


public:
	GameObject(float x, float y, float width, float height, float orientation, float speed, float angularSpeed, sf::Color color);
	GameObject(float x, float y, float size, float orientation, float speed, float angularSpeed, sf::Color color);
	~GameObject();

	sf::Shape* GetRender();

	/*void SetX(float fX, float fRatioX = 0.f)
	{
		graphic->setOrigin(fRatioX * width, graphic->getOrigin().y);
		graphic->setPosition();
	}*/

	void Move(float deltaTime);
	void Rotate(float deltaTime);
	void SetRotation(float angle);
	void Reset();
	void dirVect();
};