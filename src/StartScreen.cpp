#include <SFML/Window/Event.hpp>
#include <iostream>
#include "StartScreen.hpp"
#include "GamePlay.hpp"
StartScreen::StartScreen(std::shared_ptr<Backend> &backend, sf::RenderWindow* window) 
    : backend(backend), window(window), startButtonSelected(false), startButtonPressed(false), 
    exitButtonSelected(false), exitButtonPressed(false)
{
    
}

StartScreen::~StartScreen()
{
}


void StartScreen::Init() 
{
    backend->resources->AddTexture(BACKGROUND, "Resources/background.png");
    backend->resources->AddFont(FONT, "Resources/Dosis-Light.ttf");

    background.setTexture(backend->resources->GetTexture(BACKGROUND));
    
    title.setFont(backend->resources->GetFont(FONT));
    title.setString("Space schooter");
    title.setOrigin(title.getLocalBounds().width / 2, 0);
    title.setPosition(backend->window->getSize().x / 2, 0);

    rules.setFont(backend->resources->GetFont(FONT));
    rules.setString("You need to kill ennemies, and try not to die :)");
    rules.setOrigin(rules.getLocalBounds().width / 2, 0);
    rules.setPosition(backend->window->getSize().x / 2, title.getLocalBounds().height * 2);

    moves.setFont(backend->resources->GetFont(FONT));   
    moves.setString("A - going left, D - going right");
    moves.setOrigin(moves.getLocalBounds().width / 2, 0);
    moves.setPosition(backend->window->getSize().x / 2, rules.getLocalBounds().height * 4);

    shooting.setFont(backend->resources->GetFont(FONT));
    shooting.setString("Space for shooting");
    shooting.setOrigin(shooting.getLocalBounds().width / 2, 0);
    shooting.setPosition(backend->window->getSize().x / 2, rules.getLocalBounds().height * 6);

    startButton.setFont(backend->resources->GetFont(FONT));
    startButton.setString("Play");
    startButton.setCharacterSize(80);
    startButton.setOrigin(startButton.getLocalBounds().width / 2, 0);
    startButton.setPosition(backend->window->getSize().x / 2, rules.getLocalBounds().height * 10);

    exitButton.setFont(backend->resources->GetFont(FONT));
    exitButton.setString("Exit");
    exitButton.setCharacterSize(80);
    exitButton.setOrigin(startButton.getLocalBounds().width / 2, 0);
    exitButton.setPosition(backend->window->getSize().x / 2, rules.getLocalBounds().height * 14);

}
void StartScreen::ProcessInput() 
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
void StartScreen::Update(sf::Time deltaTime) 
{
    // for(float i =0; i < 30; i++)
    // {
    //     background.move(sf::Vector2f(0, 0.01));
    // }

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
void StartScreen::Draw() 
{
    backend->window->clear();
    backend->window->draw(background);
    backend->window->draw(title);
    backend->window->draw(rules);
    backend->window->draw(moves);
    backend->window->draw(shooting);
    backend->window->draw(startButton);
    backend->window->draw(exitButton);
    backend->window->display();
}