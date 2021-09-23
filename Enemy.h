#ifndef ENEMY_H
#define ENEMY_H

#include "Bullet.h"

class Enemy
{
private:
    sf::Texture *texture;
    sf::Sprite sprite;

    sf::Vector2f direction;


    int type;
    int HP;
    int HPmax;
    int DMGmax;
    int DMGmin;

    float DmgTime;
    float DmgTimeMax;
    sf::Vector2f velocity;

public:
    Enemy(sf::Texture * texture,sf::Vector2u windowSize,sf::Vector2f Scale,sf::Vector2f velocity,
          sf::Vector2f direction,int type, int HPmax, int DMGmax, int DMGmin);

    virtual ~Enemy();

    inline  int getDMG()const {return rand()% this->DMGmax + this->DMGmin;}
    inline  int getHP()const {return this->HP;}
    inline  int getHPmax()const {return this->HPmax;}
    inline int getType()const {return this->type;}
    const sf::FloatRect getGlobalBounds() const;
    const sf::Vector2f getPosition()const;

    void takeDMG(int DMG);
    void Update(sf::Vector2f PlayerPosition);
    void Draw(sf::RenderTarget &target);

    float vectorLength(sf::Vector2f v)
    {
        return sqrt(pow(v.x,2)+pow(v.y,2));
    }
    sf::Vector2f normalizer(sf::Vector2f v, float length)
    {
        return v/length;
    }

};


#endif // ENEMY_H
