#include <cmath>

#include "../headers/Context.hpp"
#include "../headers/Functions.hpp"
#include "../headers/Enemy.hpp"
#include "../headers/Demon.hpp"

// Private Functions
void Demon::initVariables() {
    _texture = nullptr;
    _sprite = nullptr;

    _flip = false;

    _speed = 1.f;
    _hp = 4;
    _dmg = 1;
    _xp = 10;
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
    _aggroRange.setFillColor(sf::Color::Transparent);
    _aggroRange.setOutlineColor(sf::Color::Red);
    _aggroRange.setOutlineThickness(0.3f);

    _collision.setSize(sf::Vector2f(10, 10));
    _collision.setOrigin(_sprite->getOrigin().x - 2, _sprite->getOrigin().y - 5);
    _collision.setFillColor(sf::Color::Transparent);
    _collision.setOutlineColor(sf::Color::Red);
    _collision.setOutlineThickness(0.3f);
}

void Demon::initAnimations() {
    _animationState = EnemyAnimationState::E_IDLE;
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

}

// Functions
int Demon::getDamage() {
    return _dmg;
}

void Demon::takeDamage(int damage) {
    _hp -= damage;
    if (_hp <= 0)
        listFree();
}

void Demon::takeDamage(int damage, Player* player) {
    _hp -= damage;
    if (_hp <= 0) {
        player->addXp(_xp);
        listFree();
    }
}

int Demon::getHp() {
    return _hp;
}

void Demon::updateAnimations() {
    switch (_animationState) {
        case EnemyAnimationState::E_IDLE:
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

        case EnemyAnimationState::E_WALKING:
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

        case EnemyAnimationState::E_ATTACKING:
            break;
    }
}

void Demon::update() {
    Player *player = static_cast<Player*>(Context::getEntityContext()->getEntitiesInGroup("PLAYER")->entity);
    applyBleeding();

    EntityGroupNode* group = Context::getEntityContext()->getEntitiesInGroup("WEAPON");
    if (group != nullptr && this != nullptr) {
        Weapon* weapon = static_cast<Weapon*>(group->entity);
        if (isColliding(weapon->getShape()) && weapon->isAttacking()) {
            takeDamage(player->getDamage(), player);
            _bleeding += 3;
        }
    }

    if (_hp <= 0)
        return;

    if (player->isColliding(_aggroRange)) {
        sf::Vector2f direction = player->getPosition() - _sprite->getPosition();
        direction = Functions::normalize(direction);

        _animationState = EnemyAnimationState::E_WALKING;

        if (direction.x < 0)
            _flip = true;
        else if (direction.x > 0)
            _flip = false;

        sf::FloatRect bounds = _collision.getGlobalBounds();
        if (Context::getTileMapContext()->isColliding(
            {"BACKGROUND"},
            bounds,
            sf::Vector2f(direction.x * _speed, 0)
        ) || Context::getEntityContext()->isColliding(
            {"ENEMY", "BOSS"},
            bounds,
            sf::Vector2f(direction.x * _speed, 0),
            this
        ))
            direction = sf::Vector2f(0, direction.y);

        if (Context::getTileMapContext()->isColliding(
            {"BACKGROUND"},
            bounds,
            sf::Vector2f(0, direction.y * _speed)
        ) || Context::getEntityContext()->isColliding(
            {"ENEMY", "BOSS"},
            bounds,
            sf::Vector2f(0, direction.y * _speed),
            this
        ))
            direction = sf::Vector2f(direction.x, 0);

        _sprite->move(direction * _speed);
        _aggroRange.setPosition(_sprite->getPosition());
        _collision.setPosition(_sprite->getPosition());
    } else {
        _animationState = EnemyAnimationState::E_IDLE;
    }

    updateAnimations();
};

void Demon::render(sf::RenderTarget& target) {
    target.draw(*_sprite);
    target.draw(_aggroRange);
    target.draw(_collision);
}

void Demon::listFree() {
    Context::getEntityContext()->removeFromGroup("ENEMY", this);
}