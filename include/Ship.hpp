#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Ship : public sf::Drawable 
{
private:
    sf::Sprite ship;
    sf::Sprite shield;
    
    sf::Vector2f shipScale;
    sf::Vector2f shieldScale;

    sf::Vector2f velocity;

    bool shieldActive;
    int shieldOffsetX = -22;
    int shieldOffsetY = -5;

public:
    Ship();
    ~Ship();

    void Init(const sf::Texture &shipTexture, const sf::Texture &shieldTexture);
    void Move(sf::Vector2f direction);
    void SetPosition(float position_x, float position_y);
    sf::Vector2f GetPosition();
    sf::FloatRect GetGlobalBounds();
    void ActivateShield();
    void DeactivateShield();
    bool isShieldActive();
    void SetShieldPosition();
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};