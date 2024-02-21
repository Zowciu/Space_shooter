#include "Ship.hpp"

Ship::Ship() :  shipScale({0.09f,0.09f}), shieldScale({0.14,0.14}), velocity(10.f, 10.f), shieldActive(false){

}

Ship::~Ship() {

}

void Ship::Init(const sf::Texture &shipTexture, const sf::Texture &shieldTexture)
{
    ship.setTexture(shipTexture);
    ship.setScale(shipScale);
    shield.setTexture(shieldTexture);
    shield.setScale(shieldScale);
}

void Ship::Move(sf::Vector2f direction)
{
    ship.move(direction.x*velocity.x , direction.y*velocity.y);
}

void Ship::SetPosition(float position_x, float position_y)
{
    ship.setPosition(position_x, position_y);
}

sf::Vector2f Ship::GetPosition()
{
    return ship.getPosition();
}

sf::FloatRect Ship::GetGlobalBounds()
{
    return ship.getGlobalBounds();
}

void Ship::ActivateShield()
{
    shieldActive = true;
}

void Ship::DeactivateShield()
{
    shieldActive = false;
}
bool Ship::isShieldActive()
{
    return shieldActive;
}

void Ship::SetShieldPosition() {
    shield.setPosition(ship.getPosition().x + shieldOffsetX, ship.getPosition().y + shieldOffsetY);
}

void Ship::draw(sf::RenderTarget &target, [[maybe_unused]] sf::RenderStates states) const
{
    target.draw(ship);
    if (shieldActive) {
        target.draw(shield); // Narysuj tarczę, jeśli jest aktywna
    }
}