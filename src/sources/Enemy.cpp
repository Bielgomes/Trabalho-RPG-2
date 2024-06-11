#include "../headers/Enemy.h"

// Private Functions
void Enemy::initVariables() {
    _speed = 1.f;
    _hp = 10;
    _damage = 1;
}

void Enemy::initTexture() {
    _texture = new sf::Texture();
    if (!_texture->loadFromFile("src/resources/textures/skeleton.png")) {
        std::cout << "ERROR::ENEMY::INITTEXTURE::Could not load texture file." << std::endl;
    }
}

void Enemy::initSprite() {
    _sprite = new sf::Sprite(*_texture);
    _sprite->setOrigin(_sprite->getGlobalBounds().width / 2, _sprite->getGlobalBounds().height);
    _sprite->setPosition(0.f, 0.f);
}

// Constructor and Destructor
Enemy::Enemy() {
    initVariables();
    initTexture();
    
    initSprite();
}

Enemy::~Enemy() {

}

// Accessors
const sf::Vector2f& Enemy::getPosition() const {
    return _sprite->getPosition();
}

const sf::FloatRect Enemy::getShape() const {
    return _sprite->getGlobalBounds();
}

// Functions
void Enemy::update() {
    _sprite->move(0.f, 1.0);
};

void Enemy::render(sf::RenderTarget& target) {
    target.draw(*_sprite);
}