#include <Game.h>


int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(800,920), "Space Shooter", sf::Style::Titlebar);

    //sf::Clock clock;
    //float dt;
    Game game(&window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
                window.close();
        };

        //dt = clock.restart().asSeconds();

        game.Update();
        game.Draw();



    }
    return 0;
}
