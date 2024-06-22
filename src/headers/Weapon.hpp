#pragma once

#include "CombatEntity.hpp"
#include "Item.hpp"

class Weapon : public Entity,
               public Item
{
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
        virtual bool isAttacking() = 0;

        virtual Weapon* clone() = 0;
};