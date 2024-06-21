#include <iostream>

#include "../headers/Context.hpp"
#include "../headers/Functions.hpp"
#include "../headers/Character.hpp"
#include "../headers/WeaponStaff.hpp"
#include "../headers/Projectile.hpp"

// Private Functions
void Character::initVariables() {
    _texture = nullptr;
    _sprite = nullptr;
    
    Context::getEntityContext()->addGroup("WEAPON");
    
    _weapon = new WeaponStaff(this);
    Context::getEntityContext()->addToGroup("WEAPON", _weapon);

    _flip = false;

    _hp = 100;
    _dmg = 0;
    _xp = 0;

    _velocity = sf::Vector2f(0.f, 0.f);
    _velocityMax = 1.3f;
    _velocityDesaceleration = 0.85f;
    _velocityAceleration = 1.1f;

    _isSpecialAttckButtonPressed = false;
    _specialAttackTimer.restart();
    _invencibilityTimer.restart();
}

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
Character::Character(sf::Vector2f position, std::string textureName, std::string texturePath) {
    _textureName = textureName;
    _texturePath = texturePath;

    initVariables();
    initTexture();
    initSprite();
    initAnimations();

    _sprite->setPosition(position);
}

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

void Character::update() {
    updatePhysics();
    updateMovement();

    _weapon->update();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        if (_specialAttackTimer.getElapsedTime().asSeconds() > 3.f && !_isSpecialAttckButtonPressed) {
            _isSpecialAttckButtonPressed = true;
            _specialAttackTimer.restart();

            sf::Vector2f CharacterPosition = getCenter();
            sf::Vector2f mousePosition = Context::getWindowContext()->getMousePosition(); 

            float angle = Functions::pointDirection(CharacterPosition, mousePosition);
            sf::Vector2f direction = Functions::directionTo(angle);
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

void Character::render(sf::RenderTarget& target) {
    target.draw(*_sprite);
    _weapon->render(target);
}

void Character::listFree() {
    Context::getEntityContext()->removeFromGroup("Character", this);
}