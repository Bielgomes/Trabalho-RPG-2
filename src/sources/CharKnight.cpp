#include "../headers/Context.hpp"

#include "../headers/CharKnight.hpp"
#include "../headers/WeaponSword.hpp"

// Constructor
CharKnight::CharKnight(sf::Vector2f position, std::string name) {
    _textureName = "CHARKNIGHT";
    _texturePath = "knightSpriteSheet";

    initVariables();
    initTexture();
    initSprite();
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

    _hp = 100;
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