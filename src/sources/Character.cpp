#include <iostream>

#include "../headers/Context.hpp"
#include "../headers/Functions.hpp"
#include "../headers/Character.hpp"
#include "../headers/WeaponStaff.hpp"
#include "../headers/Projectile.hpp"

// Private Functions
void Character::initTexture() {
    sf::Texture* characterTexture = Context::getTextureContext()->getTexture(_textureName);
    if (characterTexture == nullptr) {
        characterTexture = new sf::Texture();
        if (!characterTexture->loadFromFile("src/resources/textures/" + _texturePath + ".png")) {
            std::cout << "ERROR::GAME::INITTEXTURES::Could not load Character texture file." << std::endl;
        }
        Context::getTextureContext()->addTexture(_textureName, characterTexture);
    }

    _texture = characterTexture;

    sf::Texture* heartFullTexture = Context::getTextureContext()->getTexture("HEARTFULL");
    if (heartFullTexture == nullptr) {
        heartFullTexture = new sf::Texture();
        if (!heartFullTexture->loadFromFile("src/resources/textures/fullHeartSprite.png")) {
            std::cout << "ERROR::GAME::INITTEXTURES::Could not load Heart Full texture file." << std::endl;
        }
        Context::getTextureContext()->addTexture("HEARTFULL", heartFullTexture);
    }

    sf::Texture* heartEmptyTexture = Context::getTextureContext()->getTexture("HEARTEMPTY");
    if (heartEmptyTexture == nullptr) {
        heartEmptyTexture = new sf::Texture();
        if (!heartEmptyTexture->loadFromFile("src/resources/textures/emptyHeartSprite.png")) {
            std::cout << "ERROR::GAME::INITTEXTURES::Could not load Heart Empty texture file." << std::endl;
        }
        Context::getTextureContext()->addTexture("HEARTEMPTY", heartEmptyTexture);
    }
}

void Character::initSprite() {
    _sprite = new sf::Sprite(*_texture);

    _collision.setSize(sf::Vector2f(9, 12));
    _collision.setOrigin(_sprite->getOrigin().x - 3, _sprite->getOrigin().y - 13);
    _collision.setFillColor(sf::Color::Transparent);
    _collision.setOutlineColor(sf::Color::Red);
    _collision.setOutlineThickness(0.3f);
}

void Character::initAnimations() {
    _animationState = CharacterAnimationState::IDLE;
    _animationFrame = sf::IntRect(0, 0, 16, 28);

    _sprite->setTextureRect(_animationFrame);
    _animationTimer.restart();
}

// Constructor and Destructor
Character::~Character() {
    delete _sprite;
}

// Functions
int Character::getDamage() {
    return getLevel() + _weapon->getDamage() + _dmg;
}

void Character::takeDamage(int damage, sf::Vector2f direction) {
    if (_invencibilityTimer.getElapsedTime().asSeconds() > 1.5f) {
        _animationState = CharacterAnimationState::HIT;
        _hp -= damage;
        if (_hp < 0)
            _hp = 0;

        _velocity = direction * 5.f;
        
        _invencibilityTimer.restart();
    }
}

int Character::getHp() {
    return _hp;
}

void Character::addXp(int xp) {
    _xp += xp;
}

int Character::getLevel() {
    return _xp / 100;
}

void Character::updateAnimations() {
    switch (_animationState) {
        case CharacterAnimationState::IDLE:
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

        case CharacterAnimationState::WALKING:
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

        case CharacterAnimationState::HIT:
            _animationFrame.top = 56;
            _animationFrame.left = 0;
            _sprite->setTextureRect(
                sf::IntRect(_animationFrame.left + (_flip * 16), _animationFrame.top, 16 - (_flip * 32), 28)
            );

            if (_animationTimer.getElapsedTime().asSeconds() >= 0.3f) {
                _animationState = CharacterAnimationState::IDLE;
                _animationTimer.restart();
                _invencibilityTimer.restart();
            }
            break;
    }
}

void Character::updateMovement() {
    int moveX = sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    int moveY = sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W);

    sf::Vector2f direction = Functions::normalize(sf::Vector2f(moveX, moveY));
    if (_animationState == CharacterAnimationState::HIT)
        direction = sf::Vector2f(0, 0);

    _velocity.x += direction.x * _velocityAceleration;
    _velocity.y += direction.y * _velocityAceleration;

    if (_animationState != CharacterAnimationState::HIT) {
        if (std::abs(_velocity.x) > _velocityMax)
            _velocity.x = (_velocity.x < 0 ? -_velocityMax : _velocityMax) * std::abs(direction.x);
        if (std::abs(_velocity.y) > _velocityMax)
            _velocity.y = (_velocity.y < 0 ? -_velocityMax : _velocityMax) * std::abs(direction.y);

        if (_velocity.x != 0 || _velocity.y != 0)
            _animationState = CharacterAnimationState::WALKING;
        else
            _animationState = CharacterAnimationState::IDLE;
    }

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
}

void Character::render(sf::RenderTarget& target) {
    target.draw(*_sprite);
    _weapon->render(target);

    for (int i = 0; i < _hpMax; i++) {
        if (i < _hp) {
            sf::Sprite sprite = sf::Sprite(*Context::getTextureContext()->getTexture("HEARTFULL"));
            sprite.setPosition(sf::Vector2f(
                Context::getWindowContext()->getView()->getCenter().x - Context::getWindowContext()->getView()->getSize().x / 2 + 10 + i * 16,
                Context::getWindowContext()->getView()->getCenter().y - Context::getWindowContext()->getView()->getSize().y / 2 + 5
            ));
            target.draw(sprite);
        } else {
            sf::Sprite sprite = sf::Sprite(*Context::getTextureContext()->getTexture("HEARTEMPTY"));
            sprite.setPosition(sf::Vector2f(
                Context::getWindowContext()->getView()->getCenter().x - Context::getWindowContext()->getView()->getSize().x / 2 + 10 + i * 16,
                Context::getWindowContext()->getView()->getCenter().y - Context::getWindowContext()->getView()->getSize().y / 2 + 5
            ));
            target.draw(sprite);
        }
    }
}

void Character::listFree() {
    Context::getEntityContext()->removeFromGroup("CHARACTER", this);
}