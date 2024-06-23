#include "../headers/Context.hpp"

#include "../headers/CharMage.hpp"
#include "../headers/WeaponStaff.hpp"

// Constructor
CharMage::CharMage(sf::Vector2f position, std::string name) {
    _textureName = "CHARMAGE";
    _texturePath = "mageSpriteSheet";

    initVariables();
    initTexture();
    initSprite();
    initAnimations();

    _sprite->setPosition(position);

    _name = name;
}

void CharMage::initVariables() {
    _texture = nullptr;
    _sprite = nullptr;
    
    Context::getEntityContext()->addGroup("WEAPON");
    
    _weapon = new WeaponStaff(this);
    Context::getEntityContext()->addToGroup("WEAPON", _weapon);

    _flip = false;

    _hpMax = 3;
    _hp = _hpMax;
    _dmg = 0;
    _xp = 0;

    _velocity = sf::Vector2f(0.f, 0.f);
    _velocityMax = 1.3f;
    _velocityDesaceleration = 0.85f;
    _velocityAceleration = 1.1f;

    _isSpecialAttckButtonPressed = false;
    _specialAttackTimer.restart();
    _invencibilityTimer.restart();
}