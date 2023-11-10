#include <SFML/Graphics.hpp>
#include "GameObject.h"

int main()
{
<<<<<<< Updated upstream
    sf::Clock oClock;
    float fDeltaTime = 0;
    
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    //window.setFramerateLimit(60);

    GameObject rect(250.0f, 250.0f, 50.0f, 25.0f, 100.f, 100.f, sf::Color::Red);
    GameObject circle(0.0f, 0.0f, 50.0f, 50.0f, 100.f, sf::Color::Yellow);
=======
    sf::Vector2f screen = { 1280,720 };

    sf::RenderWindow window(sf::VideoMode(screen.x, screen.y), "SFML works!");

   /* GameObject::CircleDesc oDesc;
    oDesc.r = 10
    GameObject(CircleDesc)*/

    GameObject brick(800, 400, 100, 100, 0, 0, 0, sf::Color::Red);
    GameObject ball(600, 500, 100, 70, 100, 0, sf::Color::Blue);

    /*GameObject up(600, 350, 100, 100, 0, 50, 0, sf::Color::Red);
    GameObject right(600, 350, 100, 100, 90, 50, 0, sf::Color::Blue);
    GameObject down(600, 350, 100, 100, 180, 50, 0, sf::Color::Green);
    GameObject left(600, 350, 100, 100, 270, 50, 0, sf::Color::Magenta);*/

    /*GameObjectGameObject::CreateCircle()*/;

    sf::Clock clock;
    float deltaTime=0;
    float time = 0;
>>>>>>> Stashed changes

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
<<<<<<< Updated upstream
=======
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
>>>>>>> Stashed changes
        }
        
        // Déplace le rectangle en diagonale
        rect.Move(fDeltaTime);
        rect.Rotate(50, fDeltaTime);
        circle.Move(fDeltaTime);

<<<<<<< Updated upstream
=======
        //Applique le mouvement angulaire
        ball.Rotate(deltaTime);
        brick.Rotate(deltaTime);
        ball.CollisionWindow(screen);
        ball.CollisionObject(brick);
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
>>>>>>> Stashed changes
        window.clear();
        window.draw(*rect.GetRender());
        window.draw(*circle.GetRender());
        window.display();
        fDeltaTime = oClock.restart().asSeconds();
    }
    
    return 0;
}