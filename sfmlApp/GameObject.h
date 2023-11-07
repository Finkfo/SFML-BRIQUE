#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>


class GameObject
{
private:
	float x;
	float y;
	float speedX;
	float speedY;
	float width;
	float height;
	float size;
	float orientation = 0;
	sf::Color color;
	sf::Shape* graphic;

public:
	GameObject(float x,float y, float speedX, float speedY, float width, float height, sf::Color color);
	GameObject(float x, float y, float speedX, float speedY, float size, sf::Color color);

	~GameObject();

	sf::Shape*  GetRender();
	
	void Move(float fDeltaTime);
	void Rotate(float angle, float fDeltaTime);
	void setRotation(float angle);
};