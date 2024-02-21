#include <SFML/Window/Event.hpp>
#include "GamePlay.hpp"
#include "EndScreen.hpp"
#include <iostream>

GamePlay::GamePlay(std::shared_ptr<Backend> &backend, sf::RenderWindow *window)
    : backend(backend), window(window), shipDirection({0.f, 0.f}), bulletDirection(0.f, -1.f), enemyShipDirection(0.f, 1.f), score(0)
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{
    backend->resources->AddTexture(BACKGROUND, "Resources/background.png");
    backend->resources->AddTexture(SHIP, "Resources/ship.png");
    backend->resources->AddTexture(BULLET, "Resources/fire_red.png");
    backend->resources->AddTexture(ENEMYSHIP, "Resources/enemy.png");
    backend->resources->AddTexture(SHIELD, "Resources/shield.png");


    background1.setTexture(backend->resources->GetTexture(BACKGROUND));
    background2.setTexture(backend->resources->GetTexture(BACKGROUND));
    background2.setPosition(0, 0 - background1.getLocalBounds().height);
    

    ship.Init(backend->resources->GetTexture(SHIP), 
              backend->resources->GetTexture(SHIELD));

    ship.SetPosition(backend->window->getSize().x / 2,
                     backend->window->getSize().y - ship.GetGlobalBounds().height);

}

void GamePlay::ProcessInput()
{
    sf::Event event;
    while (backend->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            backend->window->close();
        }

        //Ship direction
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            shipDirection = {-1.f, 0.f};
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            shipDirection = {1.f, 0.f};
        }
        else
        {
            shipDirection = {0.f, 0.f};
        }

        // Shield
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            ship.ActivateShield();
        }
    }
}
void GamePlay::Update(sf::Time deltaTime)
{
    time += deltaTime;
    timeBullet += deltaTime;
    timeEnemy += deltaTime;
    
    //Bullets spawn
    if (timeBullet.asSeconds() > bulletSpawnTime)
    {
        auto bullet = std::make_shared<Bullet>(backend->resources->GetTexture(BULLET),
                                                sf::Vector2f(ship.GetPosition().x + ship.GetGlobalBounds().width / 4,
                                                            ship.GetPosition().y + ship.GetGlobalBounds().height / 4));
        bullets.push_back(bullet);
        timeBullet = sf::Time::Zero;
    }

    // Enemies spawn
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Setting the seed of the pseudo-random number generator based on the current time
    if (timeEnemy.asSeconds() > enemySpawnTime)
    {
        auto enemyship = std::make_shared<Enemy>(backend->resources->GetTexture(ENEMYSHIP), 
                                                sf::Vector2f( rand() % (backend->window->getSize().x - 70), 0));
        enemies.push_back(enemyship);
        timeEnemy = sf::Time::Zero;
    }

    //ship shield time
    if (ship.isShieldActive())
    {
        ship.SetShieldPosition();
        shieldTimer += deltaTime;
        if (shieldTimer.asSeconds() > 2)
        {
            ship.DeactivateShield();
            shieldTimer = sf::Time::Zero;
        }
        
    }

    if (time.asSeconds() > 0.015)
    {
        // Background movement
        background1.move(0, 1.5);
        background2.move(0, 1.5);

        if (background1.getPosition().y > backend->window->getSize().y)
        {
            background1.setPosition(0, -background1.getLocalBounds().height);
        }
        if (background2.getPosition().y > backend->window->getSize().y)
        {
            background2.setPosition(0, -background2.getLocalBounds().height);
        }

        // Ship movement
        ship.Move(shipDirection);
        if (ship.GetPosition().x <= 0.f)
        {
            ship.SetPosition(0.f, ship.GetPosition().y);
        }
        else if ((ship.GetPosition().x + ship.GetGlobalBounds().width) >= backend->window->getSize().x)
        {
            ship.SetPosition(backend->window->getSize().x - ship.GetGlobalBounds().width,
                             ship.GetPosition().y);
        }
        
        //Bullets movement
        for (auto &bulletPtr : bullets)
        {
            bulletPtr->Move(sf::Vector2f(bulletDirection));
        }

        // Enemies movement
        if (!enemies.empty())
        {
            for (auto &enemyPtr : enemies)
            {
                enemyPtr->Move(sf::Vector2f(enemyShipDirection));
            }
        }
        
        // Erasing bullets and enemies when they intersect
        for (auto bulletPtr = bullets.begin(); bulletPtr != bullets.end();)
        {
            bool bulletErased = false;
            for (auto enemyPtr = enemies.begin(); enemyPtr != enemies.end();)
            {
                if ((*bulletPtr)->GetGlobalBounds().intersects((*enemyPtr)->GetGlobalBounds()))
                {
                    bulletPtr = bullets.erase(bulletPtr);     
                    enemyPtr = enemies.erase(enemyPtr); 
                    bulletErased = true;
                    score += 10;
                }
                else
                {
                    ++enemyPtr;
                }
            }
            if (!bulletErased)
            {
                bulletPtr++;
            }
            
            
        }

        //changing state if player(ship) dies
        for (auto enemyPtr = enemies.begin(); enemyPtr != enemies.end(); enemyPtr++)
        {
            if (ship.GetGlobalBounds().intersects((*enemyPtr)->GetGlobalBounds()) && !ship.isShieldActive()) 
            {
                backend->states->AddState(std::make_unique<EndScreen>(backend, backend->window.get(), score));
            }
        }
        
        // Erasing bullet if not in window
        for (auto it = bullets.begin(); it != bullets.end();)
        {
            if ((*it)->GetPosition().y < 0)
            {
                it = bullets.erase(it);
            }
            else
            {
                it++;
            }
        }

        // Erasing enemies if not in window
        for (auto it = enemies.begin(); it != enemies.end();)
        {
            if ((*it)->GetPosition().y >= backend->window->getSize().y)
            {
                it = enemies.erase(it); 
            }
            else
            {
                it++;
            }
        }
        time = sf::Time::Zero;
    }
}

void GamePlay::Draw()
{
    backend->window->clear();
    backend->window->draw(background1);
    backend->window->draw(background2);
    backend->window->draw(ship);
    for (const auto &bulletPtr : bullets)
    {
        backend->window->draw(*bulletPtr);
    }
    for (const auto &enemyPtr : enemies)
    {
        backend->window->draw(*enemyPtr);
    }
    backend->window->display();
}