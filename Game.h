#ifndef GAME_H
#define GAME_H

#include <Player.h>
#include <Enemy.h>


class Game
{
private:
    sf::RenderWindow *window;
    //Background
    sf::Texture BackgroundT;
    sf::Sprite BackgroundS;

    //Player
    Player *player;
    sf::Texture shipT;



    //Bullets
    Bullet *bullet;
    sf::Texture bulletT;
    std::vector<Bullet*> bullets;

    //Enemies
    Enemy *enemy;
    sf::Texture enemyT;
    sf::Texture enemy1T;
    std::vector<Enemy*> enemies;
    sf::Texture BossT;

    //variables
    int shootTime;
    int shootTimeMax;
    int spawnTime;
    int spawnTimeMax;

    sf::Vector2f PlayerDirection;
    sf::Vector2f PlayerVelocity;

    //UI
    sf::Font font;
    sf::Text PlayerText;
    sf::Text PlayerStaticText;
    sf::Text enemyText;
    sf::Text GameOverText;

    sf::RectangleShape ExpBar;
    sf::RectangleShape HpBar;

public:
    Game(sf::RenderWindow *window);
    virtual ~Game();

    sf::RenderWindow& getWindow(){return *this->window;}

    void initVariables();

    //functions
    void InitUi();
    void UIUpdate();
    void UIDraw();
    void CombatUpdate();
    void Collision();
    void Update();
    void Draw();
};

#endif // GAME_H
