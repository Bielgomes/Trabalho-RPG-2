#include <cmath>

#include "../headers/Context.h"
#include "../headers/Enemy.h"
#include "../headers/Player.h"

// Private Functions
void Enemy::initVariables() {
    _texture = nullptr;
    _sprite = nullptr;

    _flip = false;

    _speed = 1.f;
    _hp = 10;
    _damage = 1;
}

void Enemy::initTexture() {
    sf::Texture* enemyTexture = Context::getTextureContext()->getTexture("ENEMY");
    if (enemyTexture == nullptr) {
        enemyTexture = new sf::Texture();
        if (!enemyTexture->loadFromFile("src/resources/textures/bigDemon.png")) {
            std::cout << "ERROR::GAME::INITTEXTURES::Could not load skeleton texture file." << std::endl;
        }
        Context::getTextureContext()->addTexture("ENEMY", enemyTexture);
    }

    _texture = enemyTexture;
}

void Enemy::initSprite() {
    _sprite = new sf::Sprite(*_texture);
    
    _aggroRange.setRadius(85.f);
    _aggroRange.setOrigin(_aggroRange.getRadius() - 16, _aggroRange.getRadius() - 16);
    _aggroRange.setFillColor(sf::Color::Transparent);
    _aggroRange.setOutlineColor(sf::Color::Red);
    _aggroRange.setOutlineThickness(0.3f);

    _collision.setSize(sf::Vector2f(12, 20));
    _collision.setOrigin(_sprite->getOrigin().x - 10, _sprite->getOrigin().y - 12);
    _collision.setFillColor(sf::Color::Transparent);
    _collision.setOutlineColor(sf::Color::Red);
    _collision.setOutlineThickness(0.3f);
}

void Enemy::initAnimations() {
    _animationState = EnemyAnimationState::E_IDLE;
    _animationFrame = sf::IntRect(0, 0, 32, 36);

    _sprite->setTextureRect(_animationFrame);
    _animationTimer.restart();
}

// Constructor and Destructor
Enemy::Enemy() {
    initVariables();
    initTexture();
    initSprite();
}

Enemy::~Enemy() {

}

// Functions
void Enemy::updateAnimations() {
    switch (_animationState) {
        case EnemyAnimationState::E_IDLE:
            _sprite->setTextureRect(sf::IntRect(0, 0, 32, 36));
            break;

        case EnemyAnimationState::E_WALKING:
            if (_animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
                _animationFrame.left += 32;
                if (_animationFrame.left >= 128)
                    _animationFrame.left = 0;

                _sprite->setTextureRect(
                    sf::IntRect(_animationFrame.left + (_flip * 32), _animationFrame.top, 32 - (_flip * 64), 36)
                );
                _animationTimer.restart();
            }
            break;

        case EnemyAnimationState::E_ATTACKING:
            break;
    }
}

void Enemy::update() {
    Player *player = static_cast<Player*>(Context::getEntityContext()->getEntitiesInGroup("PLAYER")->entity);
    if (player->isColliding(_aggroRange)) {
        sf::Vector2f direction = player->getPosition() - _sprite->getPosition();

        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0) {
            _animationState = EnemyAnimationState::E_WALKING;
            direction /= length;
        } else {
            _animationState = EnemyAnimationState::E_IDLE;
        }

        if (direction.x < 0)
            _flip = true;
        else if (direction.x > 0)
            _flip = false;

        _sprite->move(direction * _speed);
        _aggroRange.setPosition(_sprite->getPosition());
        _collision.setPosition(_sprite->getPosition());

        updateAnimations();
    }
};

void Enemy::render(sf::RenderTarget& target) {
    target.draw(*_sprite);
    target.draw(_aggroRange);
    target.draw(_collision);
}