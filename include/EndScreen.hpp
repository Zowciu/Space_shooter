#pragma once

#include "memory"
#include "State.hpp"
#include "Game.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

class EndScreen : public Engine::State
{
private:
    std::shared_ptr<Backend> backend;
    std::unique_ptr<sf::RenderWindow> window;
    sf::Sprite background;
    sf::Text gameOverText;
    sf::Text score;

    sf::Text startButton;
    sf::Text exitButton;

    bool startButtonSelected;
    bool startButtonPressed;

    bool exitButtonSelected;
    bool exitButtonPressed;

public:
    EndScreen(std::shared_ptr<Backend> &backend, sf::RenderWindow* window);
    ~EndScreen();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
};