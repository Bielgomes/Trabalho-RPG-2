#pragma once

#include "CombatEntity.h"

class Weapon : public Entity {
    protected:
        // Variables
        sf::RectangleShape _hitbox;

        sf::Clock _attackTimer;
        bool _isAttacking;
        bool _isAttackButtonPressed;

        int _dmg;

    public:
        // Constructor and Destructor
        virtual ~Weapon() = default;

        // Functions
        virtual int getDamage() = 0;
};