#ifndef BULLET_H
#define BULLET_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include<math.h>

class Bullet
{
private:

    sf::Texture *texture;
    sf::Sprite sprite;

    float velocity_x;
    float velocity_y;

public:
    Bullet(sf::Texture *texture, float pos_x, float pos_y);
    virtual ~Bullet();


    inline const sf::FloatRect getGlobalBounds() const{return this->sprite.getGlobalBounds();}
    void Update();
    void Draw(sf::RenderTarget &target);
};

#endif // BULLET_H
