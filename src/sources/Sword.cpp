#include <cmath>

#include "../headers/Context.h"
#include "../headers/Functions.h"
#include "../headers/Sword.h"
#include "../headers/Enemy.h"
#include "../headers/Player.h"

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
        if (!swordTexture->loadFromFile("src/resources/textures/knight_sword.png")) {
            std::cout << "ERROR::GAME::INITTEXTURES::Could not load knight_sword texture file." << std::endl;
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

}

// Functions
int Sword::getDamage() {
    return _dmg;
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

    if (_isAttacking) {
        EntityGroupNode* enemyNode = Context::getEntityContext()->getEntitiesInGroup("ENEMY");

        while (enemyNode != nullptr) {
            Enemy* enemy = dynamic_cast<Enemy*>(enemyNode->entity);

            if (enemy->isColliding(_hitbox))
                enemy->takeDamage(_entity->getDamage());

            if (enemy->getHp() <= 0)
               _entity->addXp(200);

            break;
            enemyNode = enemyNode->next;
        }
    }
}

void Sword::render(sf::RenderTarget& target) {
    sf::Vector2f currentPlayerPositon = _entity->getCenter();
    sf::Vector2f currentMousePosition = Context::getWindowContext()->getMousePosition();

    currentPlayerPositon.y += 5;

    float dx = currentMousePosition.x - currentPlayerPositon.x;
    float dy = currentMousePosition.y - currentPlayerPositon.y;

    float angle = atan2(dy, dx);
    float deg = angle * 180 / Functions::PI;

    _sprite->setRotation(deg + 90);
    _hitbox.setRotation(deg + 90);

    sf::Vector2f offset(std::cos(angle) * 3, std::sin(angle) * 3);
    sf::Vector2f newPosition = currentPlayerPositon + offset;

    _hitbox.setPosition(newPosition);
    _sprite->setPosition(newPosition);

    target.draw(*_sprite);
    target.draw(_hitbox);
}