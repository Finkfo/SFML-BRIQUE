#include <SFML/Graphics.hpp>
#include "Brick.h"
#include "Ball.h"
#include "Canon.h"
#include <iostream>



int main()
{
    sf::Vector2f screen = { 1280,720 };
    std::vector<Ball> balls;
    std::vector<Brick> bricks;
    int brickRow = 4;
    int brickColumn = 11;
    sf::Vector2f brickSize = { 100,50 };
    sf::Vector2f marginBricks = { (screen.x - brickColumn * 104) / 2 + brickSize.x / 2, 54 + brickSize.y / 2 };



    sf::RenderWindow window(sf::VideoMode(screen.x, screen.y), "SFML works!");

    GameObject::RectDesc canonDesc = { screen.x*0.5,700,50,100,25,100 };
    for (int j = 0; j < brickRow; j++)
    {
        for (int i = 0; i < brickColumn; i++) {
            GameObject::RectDesc brickDesc = { i*104+marginBricks.x,j*54+marginBricks.y,brickSize.x,brickSize.y};
            Brick brick(brickDesc, 10);
            bricks.push_back(brick);
        }

    }
    //Ball ball(ballDesc);
    Canon canon(canonDesc);


    sf::Clock clock;
    float deltaTime=0;
    float time = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (balls.size()<1){

                    float ballOrientation = canon.GetOrientation();
                    sf::Vector2f ballPosition = PositionCalcul(ballOrientation, canon.GetPosition(), canon.GetSize());
                    GameObject::CircleDesc ballDesc = { ballPosition.x, ballPosition.y, 20,10,10,ballOrientation,700,0,sf::Color::White };

                    Ball ball(ballDesc);
                    balls.push_back(ball);
                    std::cout << canon.GetOrientation() << std::endl;

                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
                if (bricks.size() > 0) {
                    bricks[0].LostLife();
                }
                for (int i = 0; i < bricks.size(); ++i) {
                    Brick* pBrick = &bricks[i];

                    if (pBrick->IsDead()) {
                        bricks.erase(bricks.begin() + i);
                        std::cout << bricks.size() << std::endl;
                        i--;
                    }

                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (balls.size() > 0) {
                    balls.clear();
                }

            }
        }

        //Applique le mouvement angulaire
        for (int i = 0; i < balls.size(); ++i ) {
            Ball* pBall = &balls[i];

            pBall->Update(deltaTime);
            pBall->CollisionWindow(screen);
            for (int i = 0; i < bricks.size(); ++i) {
                if (pBall->CollisionObject(bricks[i])) {
                    bricks[i].LostLife();
                }
                if (bricks[i].IsDead()) {
                    bricks.erase(bricks.begin() + i);
                    std::cout << bricks.size() << std::endl;
                    i--;
                }
            }

            if (pBall->CheckOutbounds(pBall->GetPosition(), screen)) {
                balls.erase(balls.begin() + i);
                std::cout << balls.size() << std::endl;
                --i;
            }

        }
        for (int i = 0; i < bricks.size(); i++){
            bricks[i].Update(deltaTime);
        }
        canon.Follow(window.getPosition());

        //Affichage
        window.clear(sf::Color::Blue);
        for (auto it = balls.begin(); it != balls.end(); ++it) {
            window.draw(*it->GetRender());
        }
        for (int i = 0; i < bricks.size(); i++) {
            window.draw(*bricks[i].GetRender());
        }
        window.draw(*canon.GetRender());
        window.display();

        //tempas d'un tour de boucle
        deltaTime = clock.restart().asSeconds();
    }

    return 0;
}
