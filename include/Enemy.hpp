#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
class Enemy : public sf::Drawable 
{

private:
    sf::Sprite enemy;
    int velocityY;

public:
    Enemy(const sf::Texture &texture, sf::Vector2f position);
    ~Enemy();

    void Move(sf::Vector2f direction);
    sf::Vector2f GetPosition();
    sf::FloatRect GetGlobalBounds();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};