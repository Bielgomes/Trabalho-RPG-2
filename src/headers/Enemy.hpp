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

    private:
        virtual void takeDamage(int damage, CombatEntity* player) = 0;
};