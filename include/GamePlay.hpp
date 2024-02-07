#pragma once

#include <memory>
#include <SFML/Graphics/Sprite.hpp>

#include "State.hpp"
#include "Game.hpp"
#include "Ship.hpp"

class GamePlay : public Engine::State
{
private:
    std::shared_ptr<Backend> backend;
    std::unique_ptr<sf::RenderWindow> window;

    sf::Sprite background1;
    sf::Sprite background2;
    sf::Time time;

    Ship ship;
    sf::Vector2f shipDirection;


public:
    GamePlay(std::shared_ptr<Backend> &backend, sf::RenderWindow* window);
    ~GamePlay();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
};