#include "Enemy.hpp"

Enemy::Enemy(const sf::Texture &texture, sf::Vector2f position) {

    enemy.setTexture(texture);
    enemy.setPosition(position);
    enemy.setScale({0.5f, 0.5f});
}

Enemy::~Enemy() {

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

}