#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
class Enemy : public sf::Drawable 
{

private:
    sf::Sprite enemy;

public:
    Enemy(const sf::Texture &texture, sf::Vector2f position);
    ~Enemy();

    sf::Vector2f GetPosition();
    sf::FloatRect GetGlobalBounds();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};