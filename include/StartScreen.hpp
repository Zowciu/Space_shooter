#pragma once

#include <memory>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "State.hpp"
#include "Game.hpp"

class StartScreen : public Engine::State
{
private:
    std::shared_ptr<Backend> backend;
    std::unique_ptr<sf::RenderWindow> window;

    sf::Sprite background;
    sf::Text title;
    sf::Text rules;
    sf::Text moves;
    sf::Text shooting;
    sf::Text startButton;
    sf::Text exitButton;

    bool startButtonSelected;
    bool startButtonPressed;

    bool exitButtonSelected;
    bool exitButtonPressed;

public:
    StartScreen(std::shared_ptr<Backend> &backend, sf::RenderWindow* window);
    ~StartScreen();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;

    
};