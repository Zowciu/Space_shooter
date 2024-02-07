#include <StartScreen.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

#include "Game.hpp"
Game::Game() : backend(std::make_shared<Backend>())
{
    backend->window->create(sf::VideoMode(700,800), "Space shooter", sf::Style::Close);
    backend->states->AddState(std::make_unique<StartScreen>(backend, backend->window.get()));
}

Game::~Game() {

}

void Game::Run()
{
    sf::Clock clock;
    sf::Time currentTime = sf::Time::Zero;
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Blue);

    while (backend->window->isOpen())
    {       
        // Frame rate
        currentTime += clock.restart();
        while (currentTime > tpf)
        {
            currentTime -= tpf;
            // States handling
            backend->states->ProcessStateChange();
            backend->states->GetCurrentState()->ProcessInput();
            backend->states->GetCurrentState()->Update(tpf);
            backend->states->GetCurrentState()->Draw();
            
        }
    }
}