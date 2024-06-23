#include <cmath>

#include "../headers/Context.hpp"
#include "../headers/Functions.hpp"
#include "../headers/Projectile.hpp"
#include "../headers/Enemy.hpp"
#include "../headers/Demon.hpp"


// Private Functions
void Demon::initVariables() {
    _texture = nullptr;
    _sprite = nullptr;

    _flip = false;

    _hp = 5;
    _dmg = 1;
    _xp = 10;
    _bleeding = 0;
    _bleedingTimer.restart();

    _velocity = sf::Vector2f(0.f, 0.f);
    _velocityMax = 1.25f;
    _velocityDesaceleration = 0.85f;
    _velocityAceleration = 1.1f;

    _invencibilityTimer.restart();
}

void Demon::initTexture() {
    sf::Texture* enemyTexture = Context::getTextureContext()->getTexture("ENEMY");
    if (enemyTexture == nullptr) {
        enemyTexture = new sf::Texture();
        if (!enemyTexture->loadFromFile("src/resources/textures/demonSpriteSheet.png")) {
            std::cout << "ERROR::GAME::INITTEXTURES::Could not load skeleton texture file." << std::endl;
        }
        Context::getTextureContext()->addTexture("ENEMY", enemyTexture);
    }

    _texture = enemyTexture;
}

void Demon::initSprite() {
    _sprite = new sf::Sprite(*_texture);

    _aggroRange.setRadius(100.f);
    _aggroRange.setOrigin(_aggroRange.getRadius() - 16, _aggroRange.getRadius() - 16);

    _collision.setSize(sf::Vector2f(10, 10));
    _collision.setOrigin(_sprite->getOrigin().x - 2, _sprite->getOrigin().y - 5);
}

void Demon::initAnimations() {
    _animationState = DemonAnimationState::D_IDLE;
    _animationFrame = sf::IntRect(0, 0, 16, 16);

    _sprite->setTextureRect(_animationFrame);
    _animationTimer.restart();
}

void Demon::applyBleeding() {
    if (_bleeding > 0 && _bleedingTimer.getElapsedTime().asSeconds() >= 3.f) {
        _bleedingTimer.restart();
        _bleeding--;
        takeDamage(1);
    }
}

// Constructor and Destructor
Demon::Demon() {
    initVariables();
    initTexture();
    initSprite();
}

Demon::Demon(float x, float y) {
    initVariables();
    initTexture();
    initSprite();

    _sprite->setPosition(x, y);
}

Demon::~Demon() {
    delete _sprite;
}

// Functions
void Demon::takeDamage(int damage) {
    _hp -= damage;
    if (_hp <= 0)
        listFree();
}

void Demon::takeDamage(int damage, sf::Vector2f direction) {
    _hp -= damage;
    if (_hp <= 0)
        listFree();
}

void Demon::takeDamage(int damage, CombatEntity* entity, sf::Vector2f direction) {
    _animationState = DemonAnimationState::D_HIT;
    _hp -= damage;
    if (_hp <= 0) {
        static_cast<Character*>(entity)->addXp(_xp);
        return listFree();
    }

    _velocity = direction * 1.5f;
    
    _invencibilityTimer.restart();
}

void Demon::updateAnimations() {
    switch (_animationState) {
        case DemonAnimationState::D_IDLE:
            _animationFrame.top = 0;
            if (_animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
                _animationFrame.left += 16;
                if (_animationFrame.left >= 64)
                    _animationFrame.left = 0;

                _sprite->setTextureRect(
                    sf::IntRect(_animationFrame.left + (_flip * 16), _animationFrame.top, 16 - (_flip * 32), 16)
                );
                _animationTimer.restart();
            }
            break;

        case DemonAnimationState::D_WALKING:
            _animationFrame.top = 16;
            if (_animationTimer.getElapsedTime().asSeconds() >= 0.1f) {
                _animationFrame.left += 16;
                if (_animationFrame.left >= 64)
                    _animationFrame.left = 0;

                _sprite->setTextureRect(
                    sf::IntRect(_animationFrame.left + (_flip * 16), _animationFrame.top, 16 - (_flip * 32), 16)
                );
                _animationTimer.restart();
            }
            break;

        case DemonAnimationState::D_HIT:
            _animationFrame.top = 0;
            _animationFrame.left = 0;
            _sprite->setTextureRect(
                sf::IntRect(_animationFrame.left + (_flip * 16), _animationFrame.top, 16 - (_flip * 32), 16)
            );

            if (_animationTimer.getElapsedTime().asSeconds() >= 0.3f) {
                _animationState = DemonAnimationState::D_IDLE;
                _animationTimer.restart();
                _invencibilityTimer.restart();
            }
            break;
    }
}

void Demon::updateMovement() {
    Character *character = static_cast<Character*>(Context::getEntityContext()->getEntitiesInGroup("CHARACTER")->entity);

    EntityGroupNode* group = Context::getEntityContext()->getEntitiesInGroup("WEAPON");
    if (group != nullptr) {
        Weapon* weapon = static_cast<Weapon*>(group->entity);
        if (isColliding(weapon->getShape()) && weapon->isAttacking())
            takeDamage(character->getDamage(), character, character->directionTo(this));
    }

    group = Context::getEntityContext()->getEntitiesInGroup("PROJECTILE");
    while (group != nullptr) {
        Projectile* projectile = static_cast<Projectile*>(group->entity);
        if (isColliding(projectile->getShape())) {
            takeDamage(projectile->getDamage(), character, character->directionTo(this));
            projectile->listFree();
        }
        group = group->next;
    }
    
    if (_hp <= 0)
        return;

    float isInHitAnimation = _animationState == DemonAnimationState::D_HIT;

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
            _animationState = DemonAnimationState::D_WALKING;
        else
            _animationState = DemonAnimationState::D_IDLE;
    }

    sf::FloatRect bounds = _collision.getGlobalBounds();
    if (Context::getTileMapContext()->isColliding(
        {"BACKGROUND"},
        bounds,
        sf::Vector2f(_velocity.x, 0)
    ) || Context::getEntityContext()->isColliding(
        {"ENEMY", "BOSS"},
        bounds,
        sf::Vector2f(_velocity.x, 0),
        this
    ))
        _velocity = sf::Vector2f(0, _velocity.y);

    if (Context::getTileMapContext()->isColliding(
        {"BACKGROUND"},
        bounds,
        sf::Vector2f(0, _velocity.y)
    ) || Context::getEntityContext()->isColliding(
        {"ENEMY", "BOSS"},
        bounds,
        sf::Vector2f(0, _velocity.y),
        this
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

void Demon::update() {
    applyBleeding();

    if (_hp <= 0)
        return;

    updatePhysics();
    updateMovement();
};

void Demon::listFree() {
    Context::getEntityContext()->removeFromGroup("ENEMY", this);
}