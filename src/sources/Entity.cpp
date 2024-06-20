#include "../headers/Functions.hpp"
#include "../headers/Entity.hpp"

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
sf::Vector2f Entity::directionTo(Entity* entity) {
    return Functions::normalize(entity->getCenter() - getCenter());
}

sf::Vector2f Entity::directionTo(sf::Vector2f target) {
    return Functions::directionTo(getCenter(), target);
}

sf::Vector2f Entity::directionTo(float x, float y) {
    return Functions::directionTo(getCenter(), sf::Vector2f(x, y));
}

void Entity::render(sf::RenderTarget& target) {
    target.draw(*_sprite);
}