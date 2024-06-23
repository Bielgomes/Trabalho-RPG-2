#include "../headers/ProjectileArrow.hpp"

// Constructor
ProjectileArrow::ProjectileArrow(sf::Vector2f direction, sf::Vector2f position, float rotation, int maxDistance) {
    _textureName = "PROJECTILEARROW";
    _texturePath = "arrowSprite";

    initVariables();

    _maxDistance = maxDistance;

    initTexture();
    initSprite();

    _direction = direction * _speed;
    _sprite->setPosition(position);
    _sprite->setRotation(rotation + 90);
}