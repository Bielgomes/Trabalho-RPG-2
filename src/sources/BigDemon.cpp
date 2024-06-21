#include <cmath>

#include "../headers/Context.hpp"
#include "../headers/Functions.hpp"
#include "../headers/BigDemon.hpp"

// Private Functions
void BigDemon::initVariables() {
    _texture = nullptr;
    _sprite = nullptr;

    _flip = false;

    _hp = 10;
    _dmg = 2;
    _xp = 80;
    _bleeding = 0;
    _bleedingTimer.restart();

    _velocity = sf::Vector2f(0.f, 0.f);
    _velocityMax = 1.f;
    _velocityDesaceleration = 0.85f;
    _velocityAceleration = 1.1f;

    _invencibilityTimer.restart();
}

void BigDemon::initTexture() {
    sf::Texture* enemyTexture = Context::getTextureContext()->getTexture("BOSS");
    if (enemyTexture == nullptr) {
        enemyTexture = new sf::Texture();
        if (!enemyTexture->loadFromFile("src/resources/textures/bigDemonSpriteSheet.png")) {
            std::cout << "ERROR::GAME::INITTEXTURES::Could not load skeleton texture file." << std::endl;
        }
        Context::getTextureContext()->addTexture("BOSS", enemyTexture);
    }

    _texture = enemyTexture;
}

void BigDemon::initSprite() {
    _sprite = new sf::Sprite(*_texture);
    _sprite->setScale(1.5, 1.5);
    
    _aggroRange.setRadius(200.f);
    _aggroRange.setOrigin(_aggroRange.getRadius() - 16, _aggroRange.getRadius() - 16);

    _collision.setSize(sf::Vector2f(30, 30));
    _collision.setOrigin(_sprite->getOrigin().x - 10, _sprite->getOrigin().y - 15);
}

void BigDemon::initAnimations() {
    _animationState = BigDemonAnimationState::BD_IDLE;
    _animationFrame = sf::IntRect(0, 0, 16, 16);

    _sprite->setTextureRect(_animationFrame);
    _animationTimer.restart();
}

void BigDemon::applyBleeding() {
    if (_bleeding > 0 && _bleedingTimer.getElapsedTime().asSeconds() >= 3.f) {
        takeDamage(_bleeding);
        _bleedingTimer.restart();
        _bleeding--;
    }
}

// Constructor and Destructor
BigDemon::BigDemon() {
    initVariables();
    initTexture();
    initSprite();
}

BigDemon::BigDemon(float x, float y) {
    initVariables();
    initTexture();
    initSprite();

    _sprite->setPosition(x, y);
}

BigDemon::~BigDemon() {
    delete _sprite;
}

// Functions
void BigDemon::takeDamage(int damage) {
    _hp -= damage;
    if (_hp <= 0)
        listFree();
}

void BigDemon::takeDamage(int damage, sf::Vector2f direction) {
    _hp -= damage;
    if (_hp <= 0)
        listFree();
}

void BigDemon::takeDamage(int damage, CombatEntity* entity, sf::Vector2f direction) {
    _animationState = BigDemonAnimationState::BD_HIT;
    _hp -= damage;
    if (_hp <= 0) {
        static_cast<Character*>(entity)->addXp(_xp);
        return listFree();
    }

    _velocity = direction * 1.5f;
    
    _invencibilityTimer.restart();
}

void BigDemon::updateAnimations() {
    switch (_animationState) {
        case BigDemonAnimationState::BD_IDLE:
            _animationFrame.top = 0;
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

        case BigDemonAnimationState::BD_WALKING:
            _animationFrame.top = 36;
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

        case BigDemonAnimationState::BD_HIT:
            _animationFrame.top = 0;
            _animationFrame.left = 0;
            _sprite->setTextureRect(
                sf::IntRect(_animationFrame.left + (_flip * 32), _animationFrame.top, 32 - (_flip * 64), 36)
            );

            if (_animationTimer.getElapsedTime().asSeconds() >= 0.3f) {
                _animationState = BigDemonAnimationState::BD_IDLE;
                _animationTimer.restart();
                _invencibilityTimer.restart();
            }
            break;
    }
}

void BigDemon::updateMovement() {
    Character *character = static_cast<Character*>(Context::getEntityContext()->getEntitiesInGroup("CHARACTER")->entity);

    EntityGroupNode* group = Context::getEntityContext()->getEntitiesInGroup("WEAPON");
    if (group != nullptr) {
        Weapon* weapon = static_cast<Weapon*>(group->entity);
        if (isColliding(weapon->getShape()) && weapon->isAttacking())
            takeDamage(character->getDamage(), character, character->directionTo(this));
    }

    if (_hp <= 0)
        return;

    float isInHitAnimation = _animationState == BigDemonAnimationState::BD_HIT;
    
    sf::Vector2f direction = sf::Vector2f(0, 0);
    if (character->isColliding(_aggroRange) && !isInHitAnimation)
        direction = directionTo(character);

    if (character->isColliding(_collision)) {
        character->takeDamage(_dmg, directionTo(character));
        direction = sf::Vector2f(0, 0);
    }

    _velocity.x += direction.x * _velocityAceleration;
    _velocity.y += direction.y * _velocityAceleration;

    if (!isInHitAnimation) {
        if (std::abs(_velocity.x) > _velocityMax)
            _velocity.x = (_velocity.x < 0 ? -_velocityMax : _velocityMax) * std::abs(direction.x);
        if (std::abs(_velocity.y) > _velocityMax)
            _velocity.y = (_velocity.y < 0 ? -_velocityMax : _velocityMax) * std::abs(direction.y);

        if (_velocity.x != 0 || _velocity.y != 0)
            _animationState = BigDemonAnimationState::BD_WALKING;
        else
            _animationState = BigDemonAnimationState::BD_IDLE;
    }

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

    if (_velocity.x < 0)
        _flip = true;
    else if (_velocity.x > 0)
        _flip = false;

    _sprite->move(_velocity);
    _aggroRange.setPosition(_sprite->getPosition());
    _collision.setPosition(_sprite->getPosition());

    updateAnimations();
}

void BigDemon::update() {
    applyBleeding();

    if (_hp <= 0)
        return;
    
    updatePhysics();
    updateMovement();
};

void BigDemon::listFree() {
    Context::getEntityContext()->removeFromGroup("BOSS", this);
}