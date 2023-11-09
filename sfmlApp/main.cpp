#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <iostream>



int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

    GameObject brique(600, 500, 100, 100, 0, 0, 0, sf::Color::Red);
    GameObject ball(600, 500, 100, 70, 50, 0, sf::Color::Blue);

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
                brique.HorizontalBounce();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                //right.Reset();
                ball.VerticaltBounce();
                brique.VerticaltBounce();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                //down.Reset();
                ball.HorizontalBounce();
                brique.HorizontalBounce();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                //left.Reset();
                ball.VerticaltBounce();
                brique.VerticaltBounce();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                brique.Reset();
                ball.Reset();

                /*up.Reset();
                right.Reset();
                down.Reset();
                left.Reset();*/
            }
        }

        //Applique le mouvement angulaire
        ball.Rotate(deltaTime);
        brique.Rotate(deltaTime);
        /*up.Rotate(deltaTime);
        right.Rotate(deltaTime);
        down.Rotate(deltaTime);
        left.Rotate(deltaTime);*/

        //Applique le déplacement
        ball.Move(deltaTime);
        brique.Move(deltaTime);

        /*up.Move(deltaTime);
        right.Move(deltaTime);
        down.Move(deltaTime);
        left.Move(deltaTime);*/

        //Affichage
        window.clear();
        window.draw(*ball.GetRender());
        window.draw(*brique.GetRender());

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