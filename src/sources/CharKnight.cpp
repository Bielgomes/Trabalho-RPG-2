#include "../headers/Context.hpp"
#include "../headers/Functions.hpp"

#include "../headers/InventoryMenu.hpp"
#include "../headers/ArmorStack.hpp"

#include "../headers/CharKnight.hpp"
#include "../headers/WeaponSword.hpp"

#include "../headers/ProjectileSword.hpp"

#include "../headers/Chest.hpp"

// Constructor
CharKnight::CharKnight(sf::Vector2f position, std::string name) {
    _textureName = "CHARKNIGHT";
    _texturePath = "knightSpriteSheet";

    initVariables();
    initTexture();
    initSprite();
    initText();
    initAnimations();

    _sprite->setPosition(position);
    _name = name;
}

void CharKnight::initVariables() {
    _texture = nullptr;
    _sprite = nullptr;
    
    Context::getEntityContext()->addGroup("WEAPON");
    
    _weapon = new WeaponSword(this);
    Context::getEntityContext()->addToGroup("WEAPON", _weapon);

    _flip = false;

    _hpMax = 5;
    _hp = _hpMax;
    _dmg = 0;
    _xp = 0;

    _velocity = sf::Vector2f(0.f, 0.f);
    _velocityMax = 1.25f;
    _velocityDesaceleration = 0.85f;
    _velocityAceleration = 1.1f;

    _isSpecialAttckButtonPressed = false;
    _specialAttackTimer.restart();

    _specialAttackTimerMax = 3.f;

    _invencibilityTimer.restart();

    _inventory = new Inventory(8);
    _inventory->enqueue(0, 0);
    _armorStack = new ArmorStack(8);
}

void CharKnight::update() {
    updatePhysics();
    updateMovement();

    _weapon->update();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        if (_specialAttackTimer.getElapsedTime().asSeconds() > _specialAttackTimerMax && !_isSpecialAttckButtonPressed) {
            _isSpecialAttckButtonPressed = true;
            _specialAttackTimer.restart();

            sf::Vector2f characterPosition = getCenter();
            sf::Vector2f mousePosition = Context::getWindowContext()->getMousePosition(); 

            float angle = Functions::pointDirection(characterPosition, mousePosition);
            sf::Vector2f direction = Functions::directionTo(angle);
            float rotation = Functions::angleToDegree(angle);

            sf::Vector2f projectilePoint = sf::Vector2f(
                getPosition().x + getShape().width / 2, getPosition().y + getShape().height / 2
            );

            Context::getEntityContext()->addToGroup("PROJECTILE", new ProjectileSword(
                direction, projectilePoint, rotation, 500, 1.5f
            ));
        } else {
            _isSpecialAttckButtonPressed = false;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
        EntityGroupNode* group = Context::getEntityContext()->getEntitiesInGroup("CHEST");
        while (group != nullptr && _hp > 0) {
            Chest* chest = static_cast<Chest*>(group->entity);
            if (isColliding(chest->getShape()))
                chest->open();

            group = group->next;
        }
    }

    if (_specialAttackTimer.getElapsedTime().asSeconds() >= _specialAttackTimerMax) {
        _specialAttackText->setString("CARREGADO");
        _specialAttackText->setFillColor(sf::Color::Green);
    } else {
        _specialAttackText->setString(std::to_string((int)(_specialAttackTimerMax + 1 - _specialAttackTimer.getElapsedTime().asSeconds())) + "s");
        _specialAttackText->setFillColor(sf::Color::Red);
    }
}