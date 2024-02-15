#include "Enemy.hpp"

Enemy::Enemy(const sf::Texture &texture, sf::Vector2f position) : velocityY(3) {

    enemy.setTexture(texture);
    enemy.setPosition(position);
    enemy.setScale({0.1f, 0.1f});
}

Enemy::~Enemy() {

}

void Enemy::Move(sf::Vector2f direction)
{
    enemy.move(direction.x, direction.y * velocityY);
}

sf::Vector2f Enemy::GetPosition()
{
    return enemy.getPosition();
}
sf::FloatRect Enemy::GetGlobalBounds()
{
    return enemy.getGlobalBounds();
}
void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(enemy);
}