#include <cmath>

#include "../headers/Context.h"
#include "../headers/Enemy.h"


// Private Functions
void Enemy::initVariables() {
    _texture = nullptr;
    _sprite = nullptr;

    _speed = 1.f;
    _hp = 10;
    _damage = 1;
}

void Enemy::initTexture() {
    sf::Texture* enemyTexture = Context::getTextureContext()->getTexture("ENEMY");
    if (enemyTexture == nullptr) {
        enemyTexture = new sf::Texture();
        if (!enemyTexture->loadFromFile("src/resources/textures/skeleton.png")) {
            std::cout << "ERROR::GAME::INITTEXTURES::Could not load skeleton texture file." << std::endl;
        }
        Context::getTextureContext()->addTexture("ENEMY", enemyTexture);
    }

    _texture = enemyTexture;
}

void Enemy::initSprite() {
    _sprite = new sf::Sprite(*_texture);
    _sprite->setOrigin(_sprite->getGlobalBounds().width / 2, _sprite->getGlobalBounds().height);
    _sprite->setPosition(0.f, 0.f);

    _aggroRange.setRadius(85.f);
    _aggroRange.setOrigin(_aggroRange.getRadius(), _aggroRange.getRadius() + _sprite->getGlobalBounds().height / 2);
    _aggroRange.setFillColor(sf::Color::Transparent);
    _aggroRange.setOutlineColor(sf::Color::Red);
    _aggroRange.setOutlineThickness(0.3f);

    _collision.setSize(sf::Vector2f(_sprite->getGlobalBounds().width, _sprite->getGlobalBounds().height));
    _collision.setOrigin(_sprite->getOrigin());
    _collision.setFillColor(sf::Color::Transparent);
    _collision.setOutlineColor(sf::Color::Red);
    _collision.setOutlineThickness(0.3f);
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
    Entity *player = Context::getEntityContext()->getEntitiesInGroup("PLAYER")->entity;
    if (player->getShape().intersects(_aggroRange.getGlobalBounds())) {

        sf::Vector2f direction = player->getPosition() - _sprite->getPosition();

        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0)
            direction /= length;

        if (direction.x > 0)
            _sprite->setScale(1.f, 1.f);
        else
            _sprite->setScale(-1.f, 1.f);

        _sprite->move(direction * _speed);
        _aggroRange.setPosition(_sprite->getPosition());
        _collision.setPosition(_sprite->getPosition());
    }
};

void Enemy::render(sf::RenderTarget& target) {
    target.draw(*_sprite);
    target.draw(_aggroRange);
    target.draw(_collision);
}