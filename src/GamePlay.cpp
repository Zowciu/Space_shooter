#include <SFML/Window/Event.hpp>
#include "GamePlay.hpp"
#include <iostream>

GamePlay::GamePlay(std::shared_ptr<Backend> &backend, sf::RenderWindow* window) 
    :backend(backend), window(window), shipDirection({0.f, 0.f})
{

}

GamePlay::~GamePlay() {

}

void GamePlay::Init()
{
    backend->resources->AddTexture(BACKGROUND, "Resources/background.png");
    backend->resources->AddTexture(SHIP, "Resources/ship.png");

    background1.setTexture(backend->resources->GetTexture(BACKGROUND));
    background2.setTexture(backend->resources->GetTexture(BACKGROUND));

    background2.setPosition(0, 0 - background1.getLocalBounds().height);

    ship.Init(backend->resources->GetTexture(SHIP));
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
        time = sf::Time::Zero;
    }
    
}
void GamePlay::Draw() 
{
    backend->window->clear();
    backend->window->draw(background1);
    backend->window->draw(background2);
    backend->window->draw(ship);
    backend->window->display();
}