#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <iostream>



int main()
{
    sf::Vector2f screen(1280, 720);
    sf::RenderWindow window(sf::VideoMode(screen.x, screen.y), "SFML works!");

    GameObject brick(800, 350, 100, 100, 0, 0, 0, sf::Color::Red);
    GameObject ball(600, 500, 100, 70, 100, 0, sf::Color::Blue);

    sf::Clock clock;
    float deltaTime = 0;
    float time = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                ball.HorizontalBounce();

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                ball.VerticalBounce();

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                ball.HorizontalBounce();

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                ball.VerticalBounce();

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                ball.Reset();
            }
        }

        //Applique le mouvement angulaire
        ball.Rotate(deltaTime);
        brick.Rotate(deltaTime);

        //Applique le déplacement
        ball.Move(deltaTime);
        brick.Move(deltaTime);
        ball.CollisionWindow(screen);
        //ball.CheckOBBCollision(brick);
        ball.CheckCollisions(brick);

        //Affichage
        window.clear();
        window.draw(*ball.GetRender());
        window.draw(*brick.GetRender());
        window.display();

        //tempas d'un tour de boucle
        deltaTime = clock.restart().asSeconds();
    }

    return 0;
}