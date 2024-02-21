#include "Bullet.hpp"

Bullet::Bullet(const sf::Texture &texture, sf::Vector2f position) : velocityY(4)
{
    bullet.setTexture(texture);
    bullet.setPosition(position);
    bullet.setTextureRect(sf::IntRect(96, 0, 32, 64));
}

Bullet::~Bullet()
{
}

void Bullet::Move(sf::Vector2f direction)
{
    bullet.move(direction.x, direction.y * velocityY);
}

void Bullet::SetPosition(float position_x, float position_y)
{
    bullet.setPosition(position_x, position_y);
}

sf::Vector2f Bullet::GetPosition()
{
    return bullet.getPosition();
}

sf::FloatRect Bullet::GetGlobalBounds()
{
    return bullet.getGlobalBounds();
}

void Bullet::draw(sf::RenderTarget &target, [[maybe_unused]] sf::RenderStates states) const
{
    target.draw(bullet);
}
