#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

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

    public:
        virtual void takeDamage(int damage, Player* player) = 0;
};