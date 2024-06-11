#include <cmath>
#include <iostream>

#include "../headers/Player.h"

// Private Functions
void Player::initVariables() {
    _speed = 2.f;
    _hp = 100;
    _xp = 0;
}

void Player::initTexture() {
    _texture = new sf::Texture();
    if (!_texture->loadFromFile("src/resources/textures/player.png")) {
        std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << std::endl;
    }
}

void Player::initSprite() {
    _sprite = new sf::Sprite(*_texture);
    _sprite->setOrigin(_sprite->getGlobalBounds().width / 2, _sprite->getGlobalBounds().height);
    _sprite->setPosition(0.f, 0.f);
}

// Constructor and Destructor
Player::Player() {
    initVariables();
    initTexture();
    
    initSprite();
}

Player::~Player() {
    
}

// Accessors
const sf::Vector2f& Player::getPosition() const {
    return _sprite->getPosition();
}

const sf::FloatRect Player::getShape() const {
    return _sprite->getGlobalBounds();
}

// Functions
void Player::update() {
    int moveX = sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    int moveY = sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W);

    sf::Vector2f direction(moveX * _speed, moveY * _speed);

    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction.x /= length;
        direction.y /= length;
    }

    if (direction.x > 0)
        _sprite->setScale(1.f, 1.f);
    else if (direction.x < 0)
        _sprite->setScale(-1.f, 1.f);

    _sprite->move(direction * _speed);
}