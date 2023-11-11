#include <SFML/Graphics.hpp>
#include "Brick.h"
#include "Ball.h"
#include "Canon.h"
#include <iostream>



int main()
{
    sf::Vector2f screen = { 1280,720 };

    sf::RenderWindow window(sf::VideoMode(screen.x, screen.y), "SFML works!");

    GameObject::CircleDesc ballDesc = { 200, 200, 20,10,10,30,0,0,sf::Color::White };
    GameObject::RectDesc brickDesc = { 100.f,100.f,100.f,100.f };
    GameObject::RectDesc canonDesc = { screen.x*0.5,700,100.f,200,50,200 };

    Brick brick( brickDesc, 10 );
    Ball ball(ballDesc);
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
                brick.LostLife();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                ball.HorizontalBounce();
                brick.HorizontalBounce();
                canon.SetRotation(0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                ball.VerticalBounce();
                brick.VerticalBounce();
                canon.SetRotation(45);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                ball.HorizontalBounce();
                brick.HorizontalBounce();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                ball.VerticalBounce();
                brick.VerticalBounce();
                canon.SetRotation(-45);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                brick.Reset();
                ball.Reset();

            }
        }

        //Applique le mouvement angulaire
        ball.Rotate(deltaTime);
        brick.Rotate(deltaTime);
        canon.Follow(window.getPosition());

        //Applique le déplacement
        ball.Move(deltaTime);
        brick.Move(deltaTime);

        //Affichage
        window.clear();
        window.draw(*ball.GetRender());
        window.draw(*brick.GetRender());
        window.draw(*canon.GetRender());
        window.display();

        //tempas d'un tour de boucle
        deltaTime = clock.restart().asSeconds();
    }

    return 0;
}