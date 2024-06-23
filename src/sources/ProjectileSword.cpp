#include "../headers/ProjectileSword.hpp"

// Constructor
ProjectileSword::ProjectileSword(sf::Vector2f direction, sf::Vector2f position, float rotation, int maxDistance, float size) {
    _textureName = "PROJECTILESWORD";
    _texturePath = "swordSlashSprite";

    initVariables();

    _maxDistance = maxDistance;

    initTexture();
    initSprite();

    _direction = direction * _speed;
    _sprite->setPosition(position);
    _sprite->setRotation(rotation + 90);
    _sprite->setScale(size, size);
}