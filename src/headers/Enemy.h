#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Animated.h"
#include "CombatEntity.h"

enum EnemyAnimationState {
    E_IDLE,
    E_WALKING,
    E_ATTACKING,
};

class Enemy : public CombatEntity, public Animated<EnemyAnimationState> {
    private:
        // Variables
        sf::CircleShape _aggroRange;

        // Variables
        float _speed;

        // Private Functions
        void initVariables();
        void initTexture();
        void initSprite();
        void initAnimations();

    public:
        // Constructor and Destructor
        Enemy();
        virtual ~Enemy();

        // Functions
        int getDamage();
        void takeDamage(int damage);
        int getHp();

        void updateAnimations();
        void update();
        void render(sf::RenderTarget& target);
};