#pragma once

#include "Animated.hpp"
#include "CombatEntity.hpp"
#include "Player.hpp"

class Enemy : public CombatEntity {
    protected:
        // Variables
        sf::CircleShape _aggroRange;
        sf::Clock _bleedingTimer;

        int _xp;
        int _bleeding;

        virtual void applyBleeding() = 0;
        virtual void takeDamage(int damage) = 0;
        virtual void takeDamage(int damage, CombatEntity* entity) = 0;
};