#include <iostream>

#include "../headers/Context.hpp"
#include "../headers/Functions.hpp"
#include "../headers/Player.hpp"
#include "../headers/Sword.hpp"
#include "../headers/Projectile.hpp"

// Private Functions
void Player::initVariables() {
    _texture = nullptr;
    _sprite = nullptr;
    
    Context::getEntityContext()->addGroup("WEAPON");

    _weapon = new Sword(this);
    Context::getEntityContext()->addToGroup("WEAPON", _weapon);

    _flip = false;

    _velocity = sf::Vector2f(0.f, 0.f);
    _velocityMax = 1.3f;
    _velocityDesaceleration = 0.85f;
    _velocityAceleration = 1.1f;

    _hp = 100;
    _dmg = 0;
    _xp = 0;

    _isSpecialAttckButtonPressed = false;
    _specialAttackTimer.restart();
}

void Player::initTexture() {
    sf::Texture* playerTexture = Context::getTextureContext()->getTexture("PLAYER");
    if (playerTexture == nullptr) {
        playerTexture = new sf::Texture();
        if (!playerTexture->loadFromFile("src/resources/textures/knightSpriteSheet.png")) {
            std::cout << "ERROR::GAME::INITTEXTURES::Could not load player texture file." << std::endl;
        }
        Context::getTextureContext()->addTexture("PLAYER", playerTexture);
    }

    _texture = playerTexture;
}

void Player::initSprite() {
    _sprite = new sf::Sprite(*_texture);

    _collision.setSize(sf::Vector2f(9, 12));
    _collision.setOrigin(_sprite->getOrigin().x - 3, _sprite->getOrigin().y - 13);
    _collision.setFillColor(sf::Color::Transparent);
    _collision.setOutlineColor(sf::Color::Red);
    _collision.setOutlineThickness(0.3f);
}

void Player::initAnimations() {
    _animationState = PlayerAnimationState::IDLE;
    _animationFrame = sf::IntRect(0, 0, 16, 28);

    _sprite->setTextureRect(_animationFrame);
    _animationTimer.restart();
}

// Constructor and Destructor
Player::Player(sf::Vector2f position) {
    initVariables();
    initTexture();
    initSprite();
    initAnimations();

    _sprite->setPosition(position);
}

Player::~Player() {
    delete _sprite;
}

// Functions
int Player::getDamage() {
    return getLevel() + _weapon->getDamage() + _dmg;
}

void Player::takeDamage(int damage) {
    _hp -= damage;
    if (_hp < 0)
        _hp = 0;
}

int Player::getHp() {
    return _hp;
}

void Player::addXp(int xp) {
    _xp += xp;
}

int Player::getLevel() {
    return _xp / 100;
}

void Player::updateAnimations() {
    switch (_animationState) {
        case PlayerAnimationState::IDLE:
            _animationFrame.top = 0;
            if (_animationTimer.getElapsedTime().asSeconds() >= 0.2f) {
                _animationFrame.left += 16;
                if (_animationFrame.left >= 64)
                    _animationFrame.left = 0;

                _sprite->setTextureRect(
                    sf::IntRect(_animationFrame.left + (_flip * 16), _animationFrame.top, 16 - (_flip * 32), 28)
                );
                _animationTimer.restart();
            }
            break;

        case PlayerAnimationState::WALKING:
            _animationFrame.top = 28;
            if (_animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
                _animationFrame.left += 16;
                if (_animationFrame.left >= 64)
                    _animationFrame.left = 0;

                _sprite->setTextureRect(
                    sf::IntRect(_animationFrame.left + (_flip * 16), _animationFrame.top, 16 - (_flip * 32), 28)
                );
                _animationTimer.restart();
            }
            break;
    }
}

void Player::updateMovement() {
    int moveX = sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    int moveY = sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W);

    sf::Vector2f direction = Functions::normalize(sf::Vector2f(moveX, moveY));

    _velocity.x += direction.x * _velocityAceleration;
    _velocity.y += direction.y * _velocityAceleration;

    if (std::abs(_velocity.x) > _velocityMax)
        _velocity.x = (_velocity.x < 0 ? -_velocityMax : _velocityMax) * std::abs(direction.x);
    if (std::abs(_velocity.y) > _velocityMax)
        _velocity.y = (_velocity.y < 0 ? -_velocityMax : _velocityMax) * std::abs(direction.y);

    if (_velocity.x != 0 || _velocity.y != 0)
        _animationState = PlayerAnimationState::WALKING;
    else
        _animationState = PlayerAnimationState::IDLE;

    if (_velocity.x < 0)
        _flip = true;
    else if (_velocity.x > 0)
        _flip = false;

    sf::FloatRect bounds = _collision.getGlobalBounds();
    if (Context::getTileMapContext()->isColliding(
        {"BACKGROUND"},
        bounds,
        sf::Vector2f(_velocity.x, 0)
    ))
        _velocity = sf::Vector2f(0, _velocity.y);

    if (Context::getTileMapContext()->isColliding(
        {"BACKGROUND"},
        bounds,
        sf::Vector2f(0, _velocity.y)
    ))
        _velocity = sf::Vector2f(_velocity.x, 0);
    
    _sprite->move(_velocity);
    _collision.setPosition(_sprite->getPosition());

    updateAnimations();

    _velocity *= _velocityDesaceleration;

    if (std::abs(_velocity.x) < 0.1f)
        _velocity.x = 0.f;
    if (std::abs(_velocity.y) < 0.1f)
        _velocity.y = 0.f;
}

void Player::update() {
    updateMovement();
    _weapon->update();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        if (_specialAttackTimer.getElapsedTime().asSeconds() > 3.f && !_isSpecialAttckButtonPressed) {
            _isSpecialAttckButtonPressed = true;
            _specialAttackTimer.restart();

            std::cout << "Special Attack!" << std::endl;

            sf::Vector2f playerPosition = getPosition();
            sf::Vector2f mousePosition = Context::getWindowContext()->getMousePosition(); 

            float angle = Functions::pointDirection(getCenter(), mousePosition);
            sf::Vector2f direction = Functions::normalize(Functions::pointDirection(angle));
            float rotation = Functions::angleToDegree(angle);

            sf::Vector2f projectilePoint = sf::Vector2f(
                getPosition().x + getShape().width / 2, getPosition().y + getShape().height / 2
            );

            Context::getEntityContext()->addToGroup("PROJECTILE", new Projectile(
                direction, projectilePoint, rotation
            ));

        } else {
            _isSpecialAttckButtonPressed = false;
        }
    }
}

void Player::render(sf::RenderTarget& target) {
    target.draw(*_sprite);
    target.draw(_collision);
    
    _weapon->render(target);
}

void Player::listFree() {
    Context::getEntityContext()->removeFromGroup("PLAYER", this);
}