#include <cmath>

#include "../headers/Context.hpp"
#include "../headers/Functions.hpp"
#include "../headers/BigDemon.hpp"
#include "../headers/Player.hpp"

// Private Functions
void BigDemon::initVariables() {
    _texture = nullptr;
    _sprite = nullptr;

    _flip = false;

    _speed = 1.f;
    _hp = 1;
    _dmg = 1;
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
    _aggroRange.setFillColor(sf::Color::Transparent);
    _aggroRange.setOutlineColor(sf::Color::Red);
    _aggroRange.setOutlineThickness(0.3f);

    _collision.setSize(sf::Vector2f(30, 30));
    _collision.setOrigin(_sprite->getOrigin().x - 10, _sprite->getOrigin().y - 15);
    _collision.setFillColor(sf::Color::Transparent);
    _collision.setOutlineColor(sf::Color::Red);
    _collision.setOutlineThickness(0.3f);
}

void BigDemon::initAnimations() {
    _animationState = BigDemonAnimationState::BD_IDLE;
    _animationFrame = sf::IntRect(0, 0, 16, 16);

    _sprite->setTextureRect(_animationFrame);
    _animationTimer.restart();
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

}

// Functions
int BigDemon::getDamage() {
    return _dmg;
}

void BigDemon::takeDamage(int damage) {
    _hp -= damage;
    if (_hp <= 0)
        listFree();
}

void BigDemon::takeDamage(int damage, Player* player) {
    _hp -= damage;
    if (_hp <= 0) {
        player->addXp(10);
        listFree();
    }
}

int BigDemon::getHp() {
    return _hp;
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

        case BigDemonAnimationState::BD_ATTACKING:
            break;
    }
}

void BigDemon::update() {
    Player *player = static_cast<Player*>(Context::getEntityContext()->getEntitiesInGroup("PLAYER")->entity);
    if (player->isColliding(_aggroRange)) {
        sf::Vector2f direction = player->getPosition() - _sprite->getPosition();
        direction = Functions::normalize(direction);

        _animationState = BigDemonAnimationState::BD_WALKING;

        if (direction.x < 0)
            _flip = true;
        else if (direction.x > 0)
            _flip = false;

        sf::FloatRect bounds = _collision.getGlobalBounds();
        if (Context::getTileMapContext()->isColliding(
            {"BACKGROUND"},
            bounds,
            sf::Vector2f(direction.x * _speed, 0)
        ))
            direction = sf::Vector2f(0, direction.y);

        if (Context::getTileMapContext()->isColliding(
            {"BACKGROUND"},
            bounds,
            sf::Vector2f(0, direction.y * _speed)
        ))
            direction = sf::Vector2f(direction.x, 0);

        _sprite->move(direction * _speed);
        _aggroRange.setPosition(_sprite->getPosition());
        _collision.setPosition(_sprite->getPosition());

    } else {
        _animationState = BigDemonAnimationState::BD_IDLE;
    }

    updateAnimations();
};

void BigDemon::render(sf::RenderTarget& target) {
    target.draw(*_sprite);
    target.draw(_aggroRange);
    target.draw(_collision);
}

void BigDemon::listFree() {
    Context::getEntityContext()->removeFromGroup("BOSS", this);
}