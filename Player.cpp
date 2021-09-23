#include "Player.h"



Player::Player(sf::Texture *texture, float pos_x, float pos_y)
    :LVL(1), Exp(0), HPmax(10), DMG(1), DMGMax(2), Points(0)
{
    this->texture = texture;
    this->sprite.setTexture(*this->texture);
    this->sprite.setScale(0.1f,0.1f);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width/2,this->sprite.getGlobalBounds().height/2);
    this->sprite.setPosition(pos_x/2,pos_y - 150.f);

    this->HP = HPmax;
    this->ExpNext = 15 + static_cast<int>((50/3) * ((pow(LVL,3) - 6 * pow(LVL,2)) + 17 *LVL -12));
    this->HitTimeMax = 5.f;
    this->HitTime = 0;

}

Player::~Player()
{

}

int Player::getDmg()
{
    return rand()%this->DMGMax + this->DMG;
}

void Player::DmgColor()
{
    this->sprite.setColor(sf::Color::Red);
}

void Player::UpdateLvL()
{
    if(this->Exp >= this->ExpNext)
    {
        this->LVL++;
        this->Exp -= this->ExpNext;
        this->ExpNext = static_cast<int>((50/3)*((pow(LVL,3) - 6 * pow(LVL,2)) +17 *LVL -12));

        this->Armor++;
        if(this->cooling <= 15)
        {
            this->cooling++;
        }
        this->HPmax = 10 + this->Armor;
        this->HP = HPmax;
        //std::cout<<this->HP<<"/"<<this->HPmax<<"\n";
    }
}

void Player::PointsUp()
{
    this->Points +=10;
}

void Player::getHit(int DMG)
{
    this->HP -= DMG;
    this->HitTime = 0;
}

bool Player::dead()
{
    return this->HP <= 0;
}
void Player::Movement()
{

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        Direction.x = 0.f;
        Direction.y = -1.f;
        this->Velocity.x = this->maxVelocity*this->Direction.x;
        this->Velocity.y = this->maxVelocity*this->Direction.y;;
        this->sprite.move(this->Velocity);

    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        Direction.x = 0.f;
        Direction.y = 1.f;
        this->Velocity.x = this->maxVelocity*this->Direction.x;
        this->Velocity.y = this->maxVelocity*this->Direction.y;
        this->sprite.move(this->Velocity);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        Direction.x = -1.f;
        Direction.y = 0.f;
        this->Velocity.x = this->maxVelocity*this->Direction.x;
        this->Velocity.y = this->maxVelocity*this->Direction.y;;
        this->sprite.move(this->Velocity);
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        Direction.x = 1.f;
        Direction.y = 0.f;
        this->Velocity.x = this->maxVelocity*this->Direction.x;
        this->Velocity.y = this->maxVelocity*this->Direction.y;
        this->sprite.move(this->Velocity);
    }

}
void Player::WindowBounds(sf::RenderTarget &target)
{
    if(this->sprite.getPosition().x  <= 0.f - this->sprite.getGlobalBounds().width)
    {
        this->sprite.setPosition(target.getSize().x ,this->sprite.getPosition().y);
    }
    else if(this->sprite.getPosition().x  >= target.getSize().x + this->sprite.getGlobalBounds().width)
    {
        this->sprite.setPosition(0.f - this->sprite.getGlobalBounds().width, this->sprite.getPosition().y);
    }

    if(this->sprite.getPosition().y <= 0.f)
    {
        this->sprite.setPosition(this->sprite.getPosition().x,0.f);
    }
    else if(this->sprite.getPosition().y + this->sprite.getGlobalBounds().height + 50.f >= target.getSize().y + 40.f)
    {
        this->sprite.setPosition(this->sprite.getPosition().x,target.getSize().y -
                                 this->sprite.getGlobalBounds().height - 20.f );
    }
}
void Player::Update(sf::RenderTarget &target)
{
    if(this->HitTime < this->HitTimeMax)
    {
        this->HitTime+=1.f;
    }

    if(this->ColorChange())
    {
        this->sprite.setColor(sf::Color::Red);
    }else
    {
        this->sprite.setColor(sf::Color::White);
    }
    this->Movement();
    this->WindowBounds(target);
}
void Player::Draw(sf::RenderTarget &target )
{
    target.draw(this->sprite);
}

