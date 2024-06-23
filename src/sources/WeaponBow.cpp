#include "../headers/Context.hpp"
#include "../headers/Functions.hpp"
#include "../headers/WeaponBow.hpp"
#include "../headers/Weapon.hpp"

#include "../headers/ProjectileArrow.hpp"

#include <cmath>

// Constructor
WeaponBow::WeaponBow(CombatEntity* entity)
    : Weapon(entity, "WEAPONBOW", "bowSprite") {}

// Functions
void WeaponBow::update() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (_attackTimer.getElapsedTime().asSeconds() > 1.f && !_isAttackButtonPressed) {
            _isAttacking = true;
            _isAttackButtonPressed = true;

            sf::Vector2f characterPosition = _entity->getCenter();
            sf::Vector2f mousePosition = Context::getWindowContext()->getMousePosition(); 

            float angle = Functions::pointDirection(characterPosition, mousePosition);
            sf::Vector2f direction = Functions::directionTo(angle);
            float rotation = Functions::angleToDegree(angle);

            sf::Vector2f projectilePoint = sf::Vector2f(
                _entity->getCenter().x + direction.x * 2,
                _entity->getCenter().y + direction.y * 2
            );

            Context::getEntityContext()->addToGroup("PROJECTILE", new ProjectileArrow(
                direction, projectilePoint, rotation, 300, 1.f
            ));

            _attackTimer.restart();
        } else {
            _isAttacking = false;
        }
    } else {
        _isAttackButtonPressed = false;
        _isAttacking = false;
    }

    sf::Vector2f currentCharacterPositon = _entity->getCenter();
    sf::Vector2f currentMousePosition = Context::getWindowContext()->getMousePosition();

    currentCharacterPositon.y += 5;

    float angle = Functions::pointDirection(currentCharacterPositon, currentMousePosition);
    float deg = Functions::angleToDegree(angle);

    sf::Vector2f offset(std::cos(angle) * 3, std::sin(angle) * 3);
    sf::Vector2f newPosition = currentCharacterPositon + offset;

    _sprite->setRotation(deg + 90);
    _sprite->setPosition(newPosition);
}

void WeaponBow::listFree() {
    Context::getEntityContext()->removeFromGroup("WEAPONBOW", this);
}