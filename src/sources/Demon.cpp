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
    _hp = 1;
    _dmg = 1;
}

void Demon::initTexture() {
    sf::Texture* enemyTexture = Context::getTextureContext()->getTexture("ENEMY");
    if (enemyTexture == nullptr) {
        enemyTexture = new sf::Texture();
        if (!enemyTexture->loadFromFile("src/resources/textures/bigDemonSpriteSheet.png")) {
            std::cout << "ERROR::GAME::INITTEXTURES::Could not load skeleton texture file." << std::endl;
        }
        Context::getTextureContext()->addTexture("ENEMY", enemyTexture);
    }

    _texture = enemyTexture;
}

void Demon::initSprite() {
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

void Demon::initAnimations() {
    _animationState = EnemyAnimationState::E_IDLE;
    _animationFrame = sf::IntRect(0, 0, 32, 36);

    _sprite->setTextureRect(_animationFrame);
    _animationTimer.restart();
}

// Constructor and Destructor
Demon::Demon() {
    initVariables();
    initTexture();
    initSprite();
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
        player->addXp(10);
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
                _animationFrame.left += 32;
                if (_animationFrame.left >= 128)
                    _animationFrame.left = 0;

                _sprite->setTextureRect(
                    sf::IntRect(_animationFrame.left + (_flip * 32), _animationFrame.top, 32 - (_flip * 64), 36)
                );
                _animationTimer.restart();
            }
            break;

        case EnemyAnimationState::E_WALKING:
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

        case EnemyAnimationState::E_ATTACKING:
            break;
    }
}

void Demon::update() {
    Player *player = static_cast<Player*>(Context::getEntityContext()->getEntitiesInGroup("PLAYER")->entity);
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
            "ROOM1",
            sf::FloatRect(
                bounds.left + direction.x * _speed,
                bounds.top,
                bounds.width,
                bounds.height
            )
        ))
            direction = sf::Vector2f(0, direction.y);

        if (Context::getTileMapContext()->isColliding(
            "ROOM1",
            sf::FloatRect(
                bounds.left,
                bounds.top + direction.y * _speed,
                bounds.width,
                bounds.height
            )
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