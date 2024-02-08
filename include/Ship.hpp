#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Ship : public sf::Drawable 
{
private:
    sf::Sprite ship;

    sf::Vector2f velocity;
    sf::Vector2f scale;
public:
    Ship();
    ~Ship();

    void Init(const sf::Texture &texture);
    void Move(sf::Vector2f direction);
    void SetPosition(float position_x, float position_y);
    sf::Vector2f GetPosition();
    sf::FloatRect GetGlobalBounds();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};