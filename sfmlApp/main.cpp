#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Brick.h"
#include <iostream>



int main()
{
    sf::Vector2f screen = { 1280,720 };

    sf::RenderWindow window(sf::VideoMode(screen.x, screen.y), "SFML works!");

    GameObject::CircleDesc ballDesc = { 200, 200, 100.f };
    GameObject::RectDesc testDesc = { 300,300,100.f,100.f };
    GameObject::RectDesc brickDesc = { 100.f,100.f,100.f,100.f };


    Brick test( testDesc, 1 );
    GameObject brick(brickDesc);
    GameObject ball(ballDesc);

    /*GameObject up(600, 350, 100, 100, 0, 50, 0, sf::Color::Red);
    GameObject right(600, 350, 100, 100, 90, 50, 0, sf::Color::Blue);
    GameObject down(600, 350, 100, 100, 180, 50, 0, sf::Color::Green);
    GameObject left(600, 350, 100, 100, 270, 50, 0, sf::Color::Magenta);*/


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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                //up.Reset();
                ball.HorizontalBounce();
                brick.HorizontalBounce();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                //right.Reset();
                ball.VerticalBounce();
                brick.VerticalBounce();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                //down.Reset();
                ball.HorizontalBounce();
                brick.HorizontalBounce();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                //left.Reset();
                ball.VerticalBounce();
                brick.VerticalBounce();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                brick.Reset();
                ball.Reset();

                /*up.Reset();
                right.Reset();
                down.Reset();
                left.Reset();*/
            }
        }

        //Applique le mouvement angulaire
        ball.Rotate(deltaTime);
        brick.Rotate(deltaTime);
        /*up.Rotate(deltaTime);
        right.Rotate(deltaTime);
        down.Rotate(deltaTime);
        left.Rotate(deltaTime);*/

        //Applique le déplacement
        ball.Move(deltaTime);
        brick.Move(deltaTime);

        /*up.Move(deltaTime);
        right.Move(deltaTime);
        down.Move(deltaTime);
        left.Move(deltaTime);*/

        //Affichage
        window.clear();
        window.draw(*ball.GetRender());
        window.draw(*brick.GetRender());

       /*window.draw(*up.GetRender());
        window.draw(*right.GetRender());
        window.draw(*down.GetRender());
        window.draw(*left.GetRender());*/
        window.display();

        //tempas d'un tour de boucle
        deltaTime = clock.restart().asSeconds();
    }

    return 0;
}