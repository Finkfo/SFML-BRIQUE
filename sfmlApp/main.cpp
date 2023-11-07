#include <SFML/Graphics.hpp>
#include "GameObject.h"

int main()
{
    sf::Clock oClock;
    float fDeltaTime = 0;
    
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    //window.setFramerateLimit(60);

    GameObject rect(250.0f, 250.0f, 50.0f, 25.0f, 100.f, 100.f, sf::Color::Red);
    GameObject circle(0.0f, 0.0f, 50.0f, 50.0f, 100.f, sf::Color::Yellow);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // Déplace le rectangle en diagonale
        rect.Move(fDeltaTime);
        rect.Rotate(50, fDeltaTime);
        circle.Move(fDeltaTime);

        window.clear();
        window.draw(*rect.GetRender());
        window.draw(*circle.GetRender());
        window.display();
        fDeltaTime = oClock.restart().asSeconds();
    }
    
    return 0;
}