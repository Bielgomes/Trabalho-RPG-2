#include "../headers/Context.hpp"

#include "../headers/CharArcher.hpp"
#include "../headers/WeaponBow.hpp"

// Constructor
CharArcher::CharArcher(sf::Vector2f position, std::string name) {
    _textureName = "CHARARCHER";
    _texturePath = "archerSpriteSheet";

    initVariables();
    initTexture();
    initSprite();
    initAnimations();

    _sprite->setPosition(position);

    _name = name;
}

void CharArcher::initVariables() {
    _texture = nullptr;
    _sprite = nullptr;
    
    Context::getEntityContext()->addGroup("WEAPON");
    
    _weapon = new WeaponBow(this);
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