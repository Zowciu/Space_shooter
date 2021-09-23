#include "Enemy.h"

Enemy::Enemy(sf::Texture *texture, sf::Vector2u windowSize,sf::Vector2f Scale,sf::Vector2f velocity,
             sf::Vector2f direction,int type, int HPmax, int DMGmax, int DMGmin)
{

    this->texture = texture;
    this->sprite.setTexture(*this->texture);
    this->sprite.setScale(Scale.x,Scale.y);
    this->sprite.setPosition(rand()%(windowSize.x - 40), 0);

    this->velocity = velocity;
    this->direction = direction;
    this->type = type;
    this->HPmax = HPmax;
    this->HP = this->HPmax;
    this->DMGmax = DMGmax;
    this->DMGmin = DMGmin;

    this->DmgTimeMax = 5.f;
    this->DmgTime = 0;
}

Enemy::~Enemy()
{

}

const sf::FloatRect Enemy::getGlobalBounds()const
{
    return this->sprite.getGlobalBounds();
}
const sf::Vector2f Enemy::getPosition()const
{
    return this->sprite.getPosition();
}

void Enemy::takeDMG(int DMG)
{
    this->HP -= DMG;

    this->DmgTime = this->DmgTimeMax;

    this->sprite.move(0.f,-5.f);

    if (this->HP <=0)
    {
        this->HP = 0;
    }
}



void Enemy::Update(sf::Vector2f PlayerPosition)
{
    sf::Vector2f DirectionNormalized;
    switch (this->type)
    {
    case 0:
        this->sprite.move(this->velocity.x * 10.f ,
                          this->velocity.y * 10.f);
        break;
    case 1: //Follow
        this->direction.x = PlayerPosition.x - this->sprite.getPosition().x;
        this->direction.y = PlayerPosition.y - this->sprite.getPosition().y;



        DirectionNormalized = normalizer(this->direction, this->vectorLength(this->direction));
        this->sprite.setRotation(atan2(DirectionNormalized.y,DirectionNormalized.x)* 180 /3.14 +270);

        this->sprite.move(DirectionNormalized.x*3.f,DirectionNormalized.y*3.f);
    default:
        break;
    }

    if(this->DmgTime > 0.f)
    {
        this->DmgTime -=1.f;
        this->sprite.setColor(sf::Color::Red);
    }
    else
        this->sprite.setColor(sf::Color::White);
}

void Enemy::Draw(sf::RenderTarget &target)
{
    target.draw(this->sprite);
}
