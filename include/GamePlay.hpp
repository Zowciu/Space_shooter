#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics/Sprite.hpp>

#include "State.hpp"
#include "Game.hpp"
#include "Ship.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"

class GamePlay : public Engine::State
{
private:
    std::shared_ptr<Backend> backend;
    std::unique_ptr<sf::RenderWindow> window;

    sf::Sprite background1;
    sf::Sprite background2;
    sf::Time time;
    sf::Time timeBullet;
    sf::Time timeEnemy;


    Ship ship;
    sf::Vector2f shipDirection;

    sf::Vector2f bulletDirection;
    std::vector<std::shared_ptr<Bullet>> bullets;
    int bulletSpawnTime = 2;

    sf::Vector2f enemyShipDirection;
    std::vector<std::shared_ptr<Enemy>> enemies;
    int enemySpawnTime = 2;

public:
    GamePlay(std::shared_ptr<Backend> &backend, sf::RenderWindow* window);
    ~GamePlay();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
};