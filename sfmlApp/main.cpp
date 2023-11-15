<<<<<<< Updated upstream
#include <SFML/Graphics.hpp>
#include "GameObject.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

    GameObject rect(0.0f, 0.0f, 0.2f, 0.0f, 100, 100, sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // Déplace le rectangle en diagonale
        rect.Move();

        window.clear();
        window.draw(rect.GetRender());
        window.display();
    }

=======
#include "GameManager.h"


int main()
{
    GameManager game;
    game.Launch();
>>>>>>> Stashed changes
    return 0;
}