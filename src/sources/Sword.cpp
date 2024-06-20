#include <cmath>

#include "../headers/Context.hpp"
#include "../headers/Functions.hpp"
#include "../headers/Sword.hpp"
#include "../headers/Enemy.hpp"
#include "../headers/Player.hpp"

// Private Functions
void Sword::initVariables() {
    _texture = nullptr;
    _sprite = nullptr;

    _isAttacking = false;
    _isAttackButtonPressed = false;

    _dmg = 1;

    _flip = false;
}

void Sword::initTexture() {
    sf::Texture* swordTexture = Context::getTextureContext()->getTexture("SWORD");
    if (swordTexture == nullptr) {
        swordTexture = new sf::Texture();
        if (!swordTexture->loadFromFile("src/resources/textures/swordSprite.png")) {
            std::cout << "ERROR::GAME::INITTEXTURES::Could not load sword texture file." << std::endl;
        }
        Context::getTextureContext()->addTexture("SWORD", swordTexture);
    }

    _texture = swordTexture;
}

void Sword::initSprite() {
    _sprite = new sf::Sprite(*_texture);
    _sprite->setOrigin(_sprite->getGlobalBounds().width / 2, _sprite->getGlobalBounds().height);

    _hitbox.setSize(sf::Vector2f(9, 12));
    _hitbox.setOrigin(_sprite->getOrigin());
    _hitbox.setFillColor(sf::Color::Transparent);
    _hitbox.setOutlineColor(sf::Color::Red);
    _hitbox.setOutlineThickness(0.3f);
}

// Constructor and Destructor
Sword::Sword(Player* entity) {
    _entity = entity;

    initVariables();
    initTexture();
    initSprite();
}

Sword::~Sword() {
    delete _sprite;
}

// Functions
int Sword::getDamage() {
    return _dmg;
}

bool Sword::isAttacking() {
    return _isAttacking;
}

void Sword::update() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (_attackTimer.getElapsedTime().asSeconds() > 0.1f && !_isAttackButtonPressed) {
            _isAttacking = true;
            _isAttackButtonPressed = true;
        } else {
            _isAttacking = false;
        }

        _attackTimer.restart();
    } else {
        _isAttackButtonPressed = false;
        _isAttacking = false;
    }

    sf::Vector2f currentPlayerPositon = _entity->getCenter();
    sf::Vector2f currentMousePosition = Context::getWindowContext()->getMousePosition();

    currentPlayerPositon.y += 5;

    float angle = Functions::pointDirection(currentPlayerPositon, currentMousePosition);
    float deg = Functions::angleToDegree(angle);

    _sprite->setRotation(deg + 90);
    _hitbox.setRotation(deg + 90);

    sf::Vector2f offset(std::cos(angle) * 3, std::sin(angle) * 3);
    sf::Vector2f newPosition = currentPlayerPositon + offset;

    _hitbox.setPosition(newPosition);
    _sprite->setPosition(newPosition);
}

void Sword::listFree() {
    Context::getEntityContext()->removeFromGroup("SWORD", this);
}