#include <SFML/Graphics.hpp>
#include "Brick.h"
#include "Ball.h"
#include "Canon.h"
#include <iostream>



int main()
{
    float ballSpawnTime = 1;
    float ballSpawnDelay = 0.5;
    std::vector<Ball> balls;

    sf::Vector2f screen = { 1280,720 };

    sf::RenderWindow window(sf::VideoMode(screen.x, screen.y), "SFML works!");

    GameObject::RectDesc brickDesc = { 100.f,100.f,100.f,100.f };
    GameObject::RectDesc canonDesc = { screen.x*0.5,700,50,100,25,100 };

    Brick brick( brickDesc, 10 );
    //Ball ball(ballDesc);
    Canon canon(canonDesc);


    sf::Clock clock;
    sf::Clock ballTime;
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
                if (ballSpawnTime > ballSpawnDelay) {
                    ballSpawnTime = 0;
                    float ballOrientation = canon.GetOrientation();
                    sf::Vector2f ballPosition = PositionCalcul(ballOrientation, canon.GetPosition(), canon.GetSize());
                    GameObject::CircleDesc ballDesc = { ballPosition.x, ballPosition.y, 20,10,10,ballOrientation,50,0,sf::Color::White };

                    Ball ball(ballDesc);
                    balls.push_back(ball);

                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
                brick.LostLife();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                //ball.HorizontalBounce();
                brick.HorizontalBounce();
                canon.SetRotation(0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                //ball.VerticalBounce();
                brick.VerticalBounce();
                canon.SetRotation(45);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                //ball.HorizontalBounce();
                brick.HorizontalBounce();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                //ball.VerticalBounce();
                brick.VerticalBounce();
                canon.SetRotation(-45);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                brick.Reset();
                //ball.Reset();

            }
        }

        //Applique le mouvement angulaire
        for (int i = 0; i < balls.size(); i++) {
            balls[i].Rotate(deltaTime);
            balls[i].Move(deltaTime);

        }
        brick.Rotate(deltaTime);
        canon.Follow(window.getPosition());

        //Applique le déplacement
        brick.Move(deltaTime);

        //Affichage
        window.clear();
        for (int i = 0; i < balls.size(); i++) {
            window.draw(*balls[i].GetRender());
        }
        window.draw(*brick.GetRender());
        window.draw(*canon.GetRender());
        window.display();

        //tempas d'un tour de boucle
        deltaTime = clock.restart().asSeconds();
        ballSpawnTime += ballTime.restart().asSeconds();
    }

    return 0;
}