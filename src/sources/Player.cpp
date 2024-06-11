#include <cmath>
#include <iostream>

#include "../headers/Player.h"

// Private Functions
void Player::initVariables() {
    _texture = nullptr;
    _sprite = nullptr;

    _speed = 2.f;
    _hp = 100;
    _xp = 0;
}

void Player::initSprite() {
    _sprite = new sf::Sprite(*_texture);
    _sprite->setOrigin(_sprite->getGlobalBounds().width / 2, _sprite->getGlobalBounds().height);
    _sprite->setPosition(0.f, 0.f);

    _collision.setSize(sf::Vector2f(_sprite->getGlobalBounds().width, _sprite->getGlobalBounds().height));
    _collision.setOrigin(_sprite->getOrigin());
    _collision.setFillColor(sf::Color::Transparent);
    _collision.setOutlineColor(sf::Color::Red);
    _collision.setOutlineThickness(0.3f);
}

// Constructor and Destructor
Player::Player(sf::Texture* texture) {
    initVariables();

    _texture = texture;
    
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

    sf::Vector2f direction(moveX, moveY);

    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
        direction /= length;

    if (direction.x > 0)
        _sprite->setScale(1.f, 1.f);
    else if (direction.x < 0)
        _sprite->setScale(-1.f, 1.f);

    _sprite->move(direction * _speed);
    _collision.setPosition(_sprite->getPosition());
}

void Player::render(sf::RenderTarget& target) {
    target.draw(*_sprite);
    target.draw(_collision);
}