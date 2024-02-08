#include <SFML/Window/Event.hpp>
#include "GamePlay.hpp"
#include <iostream>

GamePlay::GamePlay(std::shared_ptr<Backend> &backend, sf::RenderWindow* window) 
    :backend(backend), window(window), shipDirection({0.f, 0.f}), bulletDirection(0.f, -1.f)
{

}

GamePlay::~GamePlay() {

}

void GamePlay::Init()
{
    backend->resources->AddTexture(BACKGROUND, "Resources/background.png");
    backend->resources->AddTexture(SHIP, "Resources/ship.png");
    backend->resources->AddTexture(BULLET, "Resources/fire_red.png");

    background1.setTexture(backend->resources->GetTexture(BACKGROUND));
    background2.setTexture(backend->resources->GetTexture(BACKGROUND));

    background2.setPosition(0, 0 - background1.getLocalBounds().height);

    ship.Init(backend->resources->GetTexture(SHIP));
    ship.SetPosition(backend->window->getSize().x / 2, 
                     backend->window->getSize().y - ship.GetGlobalBounds().height);

    //bullet.Init(backend->resources->GetTexture(BULLET));

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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
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

        //Bullet
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            auto bullet = std::make_shared<Bullet>(backend->resources->GetTexture(BULLET), 
                                                   sf::Vector2f(ship.GetPosition().x + ship.GetGlobalBounds().width / 4,
                                                                 ship.GetPosition().y + ship.GetGlobalBounds().height / 4));
            bullets.push_back(bullet);
        }
        
    }
    
}
void GamePlay::Update(sf::Time deltaTime)
{
    time += deltaTime;
    
    if(time.asSeconds() > 0.015)
    {
        //Background movement
        background1.move(0, 2.f);
        background2.move(0, 2.f);

        if (background1.getPosition().y > backend->window->getSize().y) {
        background1.setPosition(0, -background1.getLocalBounds().height);
        }
        if (background2.getPosition().y > backend->window->getSize().y) {
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
        for (auto& bulletPtr : bullets) 
        {
            bulletPtr->Move(sf::Vector2f(bulletDirection));
        }

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
        

        time = sf::Time::Zero;
    }

    
}
void GamePlay::Draw() 
{
    backend->window->clear();
    backend->window->draw(background1);
    backend->window->draw(background2);
    backend->window->draw(ship);
    //backend->window->draw(bullet);
    for (const auto& bulletPtr : bullets) {
        backend->window->draw(*bulletPtr);
    }
    backend->window->display();
}