#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Bullet : public sf::Drawable
{
private:
    sf::Sprite bullet;

    //sf::Vector2f velocity;
    
public:
    Bullet(const sf::Texture &texture, sf::Vector2f position);
    ~Bullet();

    void Init(const sf::Texture &texture);
    void Move(sf::Vector2f direction);

    void SetPosition(float position_x, float position_y);
    sf::Vector2f GetPosition();
    sf::FloatRect GetGlobalBounds();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};