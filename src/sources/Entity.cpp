#include "../headers/Entity.h"

// Accessors
const sf::Vector2f& Entity::getPosition() const {
    return _sprite->getPosition();
}

const sf::FloatRect Entity::getShape() const {
    return _sprite->getGlobalBounds();
}

const sf::Vector2f Entity::getCenter() const {
    return sf::Vector2f(
        _sprite->getPosition().x + _sprite->getGlobalBounds().width / 2,
        _sprite->getPosition().y + _sprite->getGlobalBounds().height / 2
    );
}

// Functions
void Entity::render(sf::RenderTarget& target) {
    target.draw(*_sprite);
}