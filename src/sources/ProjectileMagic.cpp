#include "../headers/ProjectileMagic.hpp"

// Constructor
ProjectileMagic::ProjectileMagic(sf::Vector2f direction, sf::Vector2f position, float rotation, int maxDistance, float size) {
    _textureName = "PROJECTILEMAGIC";
    _texturePath = "fireBallSprite";

    initVariables();

    _maxDistance = maxDistance;

    initTexture();
    initSprite();

    _direction = direction * _speed;
    _sprite->setPosition(position);
    _sprite->setRotation(rotation + 90);
    _sprite->setScale(size, size);
}