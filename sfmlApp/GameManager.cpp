#include "GameManager.h"

GameManager::GameManager() {
}
GameManager::~GameManager() {
}

void GameManager::Launch() {


    sf::RenderWindow window(sf::VideoMode(screen.x, screen.y), "SFML works!");
    CreateBricks();
    //Ball ball(ballDesc);
    CreateCanons();


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
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (balls.size() < 1) {

                    CreateBalls();

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
            /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            }*/
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (balls.size() > 0) {
                    balls.clear();
                }

            }
        }

        //Applique le mouvement angulaire
        for (int i = 0; i < balls.size(); ++i) {
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
        for (int i = 0; i < bricks.size(); i++) {
            bricks[i].Update(deltaTime);
        }
        canons[0].Follow(window.getPosition());

        //Affichage
        window.clear(sf::Color::Blue);
        for (auto it = balls.begin(); it != balls.end(); ++it) {
            window.draw(*it->GetRender());
        }
        for (int i = 0; i < bricks.size(); i++) {
            window.draw(*bricks[i].GetRender());
        }
        window.draw(*canons[0].GetRender());
        window.display();

        //tempas d'un tour de boucle
        deltaTime = clock.restart().asSeconds();
    }
}




void GameManager::CreateBricks() {

    for (int j = 0; j < brickRow; j++)
    {
        for (int i = 0; i < brickColumn; i++) {
            sf::Vector2f brickOrigin = { i * 104 + marginBricks.x, j * 54 + marginBricks.y };
            GameObject::RectDesc brickDesc = { brickOrigin.x,brickOrigin.y, brickSize.x,brickSize.y,brickSize.x / 2 ,brickSize.y / 2, 0, 0,0,  sf::Color(0,255 ,0) };

            if (i * j * brickRow <= brickRow*brickColumn/2) {
                brickDesc = { brickOrigin.x,brickOrigin.y, brickSize.x,brickSize.y,brickSize.x / 2 ,brickSize.y / 2, 0, 0,0,  sf::Color(255 ,0,0) };
            }
            else {
                brickDesc = { brickOrigin.x,brickOrigin.y, brickSize.x,brickSize.y,brickSize.x / 2 ,brickSize.y / 2, 0, 0,0,  sf::Color(0,255 ,0) };
            }
            Brick brick(brickDesc, 10);
            bricks.push_back(brick);
        }

    }
}

void GameManager::CreateBalls() {
    float ballOrientation = canons[0].GetOrientation();
    sf::Vector2f ballPosition = PositionCalcul(ballOrientation, canons[0].GetPosition(), canons[0].GetSize());
    GameObject::CircleDesc ballDesc = { ballPosition.x, ballPosition.y, 20,10,10,ballOrientation,700,0,sf::Color::White };

    Ball ball(ballDesc);
    balls.push_back(ball);
    std::cout << canons[0].GetOrientation() << std::endl;
}



void GameManager::CreateCanons() {
    Canon canon(canonDesc);
    canons.push_back(canon);
}