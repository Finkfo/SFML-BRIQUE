#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>


class GameObject
{
<<<<<<< Updated upstream
=======

private:

	std::vector<GameObject>* collisions;
	bool wasColliding = false;

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



>>>>>>> Stashed changes
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