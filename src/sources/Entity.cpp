#include "../headers/Entity.h"

// Accessors
const sf::Vector2f& Entity::getPosition() const {
    return _sprite->getPosition();
}

const sf::FloatRect Entity::getShape() const {
    return _sprite->getGlobalBounds();
}

// Functions
void Entity::render(sf::RenderTarget& target) {
    target.draw(*_sprite);
}