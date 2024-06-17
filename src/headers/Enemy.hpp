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

        int _xp;

    public:
        virtual void takeDamage(int damage, Player* player) = 0;
};