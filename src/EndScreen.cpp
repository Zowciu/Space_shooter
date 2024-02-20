#include "EndScreen.hpp"
#include <SFML/Window/Event.hpp>
#include "GamePlay.hpp"
#include <iostream>
EndScreen::EndScreen(std::shared_ptr<Backend> &backend, sf::RenderWindow* window, int &score)
    : backend(backend),  window(window), score(score), startButtonSelected(false), startButtonPressed(false), 
    exitButtonSelected(false), exitButtonPressed(false)
{

}
EndScreen::~EndScreen()
{
}

void EndScreen::Init()
{
    background.setTexture(backend->resources->GetTexture(BACKGROUND));

    gameOverText.setFont(backend->resources->GetFont(FONT));
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(100);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2, 0);
    gameOverText.setPosition(backend->window->getSize().x / 2, 0);

    scoreText.setFont(backend->resources->GetFont(FONT));
    scoreText.setString("Score: ");
    scoreText.setCharacterSize(60);
    scoreText.setOrigin(scoreText.getLocalBounds().width / 2, 0);
    scoreText.setPosition(backend->window->getSize().x / 2, gameOverText.getLocalBounds().height * 2);
    
    scoreString = std::to_string(score);
    scoreIntText.setFont(backend->resources->GetFont(FONT));
    scoreIntText.setString(scoreString);
    scoreIntText.setCharacterSize(60);
    scoreIntText.setOrigin(scoreText.getLocalBounds().width / 2, 0);
    scoreIntText.setPosition(backend->window->getSize().x / 2 + scoreText.getGlobalBounds().width, gameOverText.getLocalBounds().height * 2);


    startButton.setFont(backend->resources->GetFont(FONT));
    startButton.setString("Play again");
    startButton.setCharacterSize(80);
    startButton.setOrigin(startButton.getLocalBounds().width / 2, 0);
    startButton.setPosition(backend->window->getSize().x / 2, gameOverText.getLocalBounds().height * 6.5);

    exitButton.setFont(backend->resources->GetFont(FONT));
    exitButton.setString("Exit");
    exitButton.setCharacterSize(80);
    exitButton.setOrigin(exitButton.getLocalBounds().width / 2, 0);
    exitButton.setPosition(backend->window->getSize().x / 2, gameOverText.getLocalBounds().height * 8);
}
void EndScreen::ProcessInput()
{
    sf::Event event;
    while (backend->window->pollEvent(event))
    {
        
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        sf::FloatRect startButtonBounds = startButton.getGlobalBounds();
        sf::FloatRect exitButtonBounds = exitButton.getGlobalBounds();
        if (event.type == sf::Event::Closed)
        {
            backend->window->close();
        }

        if (startButtonBounds.contains(static_cast<sf::Vector2f>(mousePos)))
        {
            startButtonSelected = true;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                startButtonPressed = true;
            }
            
        }
        else
        {
            startButtonSelected = false;
        }

        if (exitButtonBounds.contains(static_cast<sf::Vector2f>(mousePos)))
        {
            exitButtonSelected = true;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                exitButtonPressed = true;
            }
            
        }
        else
        {
            exitButtonSelected = false;
        }
    }
}
void EndScreen::Update(sf::Time deltaTime)
{
    
    if (startButtonSelected)
    {
        startButton.setFillColor(sf::Color::Green);
    }
    else
    {
        startButton.setFillColor(sf::Color::White);
    }

    if (exitButtonSelected)
    {
        exitButton.setFillColor(sf::Color::Red);
    }
    else
    {
        exitButton.setFillColor(sf::Color::White);
    }

    if (startButtonPressed)
    {
        backend->states->AddState(std::make_unique<GamePlay>(backend, window.get()), true);
        startButtonPressed = false;
    }

    if (exitButtonPressed)
    {
        backend->window->close();
    }
}
void EndScreen::Draw()
{
    backend->window->clear();
    backend->window->draw(background);
    backend->window->draw(gameOverText);
    backend->window->draw(scoreText);
    backend->window->draw(scoreIntText);
    backend->window->draw(startButton);
    backend->window->draw(exitButton);
    backend->window->display();
}