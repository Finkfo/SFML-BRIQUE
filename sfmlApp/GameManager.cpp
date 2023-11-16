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
    CreateBorders();
    CreateRaquette();


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
        for (int i = 0; i < balls.size(); ++i) {
            Ball* pBall = &balls[i];

            pBall->Update(deltaTime);
            //pBall->CollisionWindow(screen);

            pBall->CheckCollisions(raquettes[0]);
            for (int i = 0; i < windowBorders.size(); ++i) {
                pBall->CheckCollisions(windowBorders[i]);
            }
            for (int i = 0; i < bricks.size(); ++i) {
                if (pBall->CheckCollisions(bricks[i])) {
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
        sf::Vector2i screen = window.getPosition();
        canons[0].Follow(screen);
        raquettes[0].RaquetteFollow(screen);

        //Affichage
        window.clear(sf::Color::Blue);
        for (auto it = balls.begin(); it != balls.end(); ++it) {
            window.draw(*it->GetRender());
        }
        for (int i = 0; i < bricks.size(); i++) {
            window.draw(*bricks[i].GetRender());
        }

        for (int i = 0; i < windowBorders.size(); i++) {
            window.draw(*windowBorders[i].GetRender());
        }
        window.draw(*canons[0].GetRender());
        window.draw(*raquettes[0].GetRender());
        window.display();

        //tempas d'un tour de boucle
        deltaTime = clock.restart().asSeconds();
    }
}

void GameManager::CreateBricks() {
    int brickNumber = brickColumn * brickRow;
    for (int j = 0; j < brickRow; j++)
    {
        for (int i = 0; i < brickColumn; i++) {
            sf::Vector2f brickOrigin = { i * 104 + marginBricks.x, j * 54 + marginBricks.y };
            float R = (j + i) > (brickNumber) ? 0 : (j + i) > (brickNumber / 3.5) ? 40 : (j + i) > (brickNumber / 4) ? 80 : (j + i) > (brickNumber / 4.25) ? 120 : (j + i) > (brickNumber / 4.5) ? 160 : (j + i) > (brickNumber / 5) ? 200 : (j + i) > (brickNumber / 6) ? 240 : 255;
            float G = (j + i) < (brickNumber / 44) ? 0 : (j + i) < (brickNumber / 22) ? 40 : (j + i) < (brickNumber / 12) ? 80 : (j + i) < (brickNumber / 11) ? 120 : (j + i) < (brickNumber / 8) ? 160 : (j + i) < (brickNumber / 7) ? 200 : (j + i) < (brickNumber / 6) ? 240 : 255;
            float B = 255;
            GameObject::RectDesc brickDesc = { brickOrigin.x,brickOrigin.y, brickSize.x,brickSize.y,brickSize.x / 2 ,brickSize.y / 2, 0, 0,0,  sf::Color(R,G ,B) };


            Brick brick(brickDesc, 10);
            bricks.push_back(brick);
        }

    }
}

void GameManager::CreateBalls() {
    float ballOrientation = canons[0].GetOrientation();
    sf::Vector2f ballPosition = PositionCalcul(ballOrientation, canons[0].GetPosition(), canons[0].GetSize());
    GameObject::CircleDesc ballDesc = { ballPosition.x, ballPosition.y, 20,10,10,ballOrientation,1500,0,sf::Color::White };

    Ball ball(ballDesc);
    balls.push_back(ball);
    std::cout << canons[0].GetOrientation() << std::endl;
}



void GameManager::CreateCanons() {
    Canon canon(canonDesc);
    canons.push_back(canon);
}

void GameManager::CreateBorders() {
    GameObject::RectDesc windowBordersDescLeft = { -50,0,100,screen.y*2 };
    GameObject windowBorderLeft(windowBordersDescLeft);
    windowBorders.push_back(windowBorderLeft);

    GameObject::RectDesc windowBordersDescUp = { 0,-50,screen.x*2,100 };
    GameObject windowBorderUp(windowBordersDescUp);
    windowBorders.push_back(windowBorderUp);

    GameObject::RectDesc windowBordersDescRight = { screen.x+50,0,100,screen.y*2 };
    GameObject windowBorderRight(windowBordersDescRight);
    windowBorders.push_back(windowBorderRight);
}

void GameManager::CreateRaquette() {
    GameObject::RectDesc RaquetteDesc = { screen.x/2,screen.y-20,150,10 };
    Raquette raquette(RaquetteDesc);
    raquettes.push_back(raquette);
}