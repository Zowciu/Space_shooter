#include "Ship.hpp"
#include <SFML/Graphics.hpp>
Ship::Ship() : velocity(10.f, 10.f), scale(0.09f,0.09f){

}

Ship::~Ship() {

}

void Ship::Init(const sf::Texture &texture)
{
    ship.setTexture(texture);
    ship.setScale(sf::Vector2f(scale));
}

void Ship::Move(sf::Vector2f direction)
{
    ship.move(direction.x*velocity.x, direction.y*velocity.y);
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
void Ship::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(ship);
}