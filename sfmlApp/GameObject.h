#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>


class GameObject
{
<<<<<<< Updated upstream
=======
//public:
//
//	typedef struct RectDesc
//	{
//		float x;
//		float y;
//		float w;
//		float h;
//		float orientation = 0;
//		float speed = 0;
//		float angularSpeed = 0;
//		sf::Color color = sf::Color::Red;
//	};
//
//	typedef struct CircleDesc 
//	{
//		float x;
//		float y;
//		float r;
//	};

>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
public:
	GameObject(float x,float y, float speedX, float speedY, float width, float height, sf::Color color);
	GameObject(float x, float y, float speedX, float speedY, float size, sf::Color color);
=======
	//std::vector<int> a = { (0,0,0) };
	
public:
	GameObject(float x, float y, float width, float height, float orientation, float speed, float angularSpeed , sf::Color color);
	GameObject(float x, float y, float size, float orientation, float speed, float angularSpeed , sf::Color color);

	//typedef struct CircleDesc
	//{
	//	float x = 0;
	//	float y = 0;
	//	float r;
	//};

	//typedef struct RectDesc
	//{
	//	float x;
	//	float y;
	//	float w;
	//	float h;
	//};
>>>>>>> Stashed changes

	~GameObject();

	sf::Shape*  GetRender();
	
<<<<<<< Updated upstream
	void Move(float fDeltaTime);
	void Rotate(float angle, float fDeltaTime);
	void setRotation(float angle);
};
=======

	void Move(float deltaTime);
	void Rotate(float deltaTime);
	void SetRotation(float angle);
	void HorizontalBounce();
	void VerticalBounce();
	void Reset();
	void CollisionWindow(sf::Vector2f screen);
	void CollisionObject(GameObject& other);
};

/*Calcul angle canon = angle entre vecteur x(1,0) et vecteur souris = (xsouris-xcanon,ysouris-ycanon)
* angle entre vecteur = acos(<u°v>/(module(u)*module(v)))
*/
>>>>>>> Stashed changes
