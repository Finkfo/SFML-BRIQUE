#pragma once
#include <SFML/Graphics.hpp>
#include "Brick.h"
#include "Ball.h"
#include "Canon.h"
#include <iostream>
class GameManager
{
private:
    sf::Vector2f screen = { 1280,720 };
    GameObject::RectDesc canonDesc = { float(screen.x * 0.5),700,50,100,25,100 };
    std::vector<GameObject> windowBorders;
    std::vector<Ball> balls;
    std::vector<Brick> bricks;
    std::vector<Canon> canons;
    int brickRow = 4;
    int brickColumn = 11;
    sf::Vector2f brickSize = { 100,50 };
    sf::Vector2f marginBricks = { (screen.x - brickColumn * 104) / 2 + brickSize.x / 2, 54 + brickSize.y / 2 };

public:
    GameManager();
    ~GameManager();
    void Launch();
    void CreateBricks();
    void CreateBalls();
    void CreateCanons();
    void CreateBorders();
};

