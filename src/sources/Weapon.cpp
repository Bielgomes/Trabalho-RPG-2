#include <cmath>

#include "../headers/Context.hpp"
#include "../headers/Functions.hpp"

#include "../headers/Weapon.hpp"
#include "../headers/Enemy.hpp"

// Private Functions
void Weapon::initVariables() {
    _texture = nullptr;
    _sprite = nullptr;

    _isAttacking = false;
    _isAttackButtonPressed = false;

    _dmg = 1;

    _flip = false;
}

void Weapon::initTexture() {
    sf::Texture* weaponTexture = Context::getTextureContext()->getTexture(_textureName);
    if (weaponTexture == nullptr) {
        weaponTexture = new sf::Texture();
        if (!weaponTexture->loadFromFile("src/resources/textures/" + _texturePath + ".png")) {
            std::cout << "ERROR::GAME::INITTEXTURES::Could not load weapon texture file." << std::endl;
        }
        Context::getTextureContext()->addTexture(_textureName, weaponTexture);
    }

    _texture = weaponTexture;
}

void Weapon::initSprite() {
    _sprite = new sf::Sprite(*_texture);
    _sprite->setOrigin(_sprite->getGlobalBounds().width / 2, _sprite->getGlobalBounds().height);

    _hitbox.setSize(sf::Vector2f(9, 12));
    _hitbox.setOrigin(_sprite->getOrigin());
    _hitbox.setFillColor(sf::Color::Transparent);
    _hitbox.setOutlineColor(sf::Color::Red);
    _hitbox.setOutlineThickness(0.3f);
}

// Constructor and Destructor
Weapon::Weapon(CombatEntity* entity, std::string textureName, std::string texturePath) {
    _textureName = textureName;
    _texturePath = texturePath;

    _entity = entity;

    initVariables();
    initTexture();
    initSprite();
}

Weapon::~Weapon() {
    delete _sprite;
}

// Functions
int Weapon::getDamage() {
    return _dmg;
}

bool Weapon::isAttacking() {
    return _isAttacking;
}

void Weapon::update() {
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

    sf::Vector2f currentCharacterPositon = _entity->getCenter();
    sf::Vector2f currentMousePosition = Context::getWindowContext()->getMousePosition();

    currentCharacterPositon.y += 5;

    float angle = Functions::pointDirection(currentCharacterPositon, currentMousePosition);
    float deg = Functions::angleToDegree(angle);

    _sprite->setRotation(deg + 90);
    _hitbox.setRotation(deg + 90);

    sf::Vector2f offset(std::cos(angle) * 3, std::sin(angle) * 3);
    sf::Vector2f newPosition = currentCharacterPositon + offset;

    _hitbox.setPosition(newPosition);
    _sprite->setPosition(newPosition);
}

void Weapon::listFree() {
    Context::getEntityContext()->removeFromGroup("WEAPON", this);
}