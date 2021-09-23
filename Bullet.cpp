#include "Bullet.h"

Bullet::Bullet(sf::Texture *texture, float pos_x, float pos_y)
{
    this->texture = texture;
    this->sprite.setTexture(*this->texture);
    this->sprite.setTextureRect(sf::IntRect(96,0,32,64));
    this->sprite.setPosition(pos_x+18,pos_y);


    this->velocity_x = 0.0f;
    this->velocity_y = -10.f;
}

Bullet::~Bullet()
{

}

void Bullet::Update()
{
    this->sprite.move(this->velocity_x, this->velocity_y);
}

void Bullet::Draw(sf::RenderTarget &target)
{
    target.draw(this->sprite);
}
