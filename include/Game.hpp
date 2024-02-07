#pragma once

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "StateManager.hpp"
#include "ResourcesManager.hpp"

enum ResourcesId
{
    FONT = 0,
    BACKGROUND = 1,
    SHIP = 2
};

struct Backend
{
    std::unique_ptr<Engine::StateManager> states;
    std::unique_ptr<Engine::ResourcesManager> resources;
    std::unique_ptr<sf::RenderWindow> window;

    Backend()
    {
        states = std::make_unique<Engine::StateManager>();
        resources = std::make_unique<Engine::ResourcesManager>();
        window = std::make_unique<sf::RenderWindow>();
        
    }
};


class Game {
private:
    std::shared_ptr<Backend> backend;
    const sf::Time tpf = sf::seconds(1.f/60.f);

public:
    Game();
    ~Game();

    void Run();
};