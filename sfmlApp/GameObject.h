#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>


class GameObject
{
public:
	GameObject(float x,float y, float speedX, float speedY, int width, int height, sf::Color color);
	~GameObject();

	sf::RectangleShape GetRender();
	
	void Move();

private:
	float x;
	float y;
	float speedX;
	float speedY;
	int width;
	int height;
	sf::Color color;
	sf::RectangleShape graphic;
};