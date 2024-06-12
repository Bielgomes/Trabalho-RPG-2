#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Animated.h"
#include "Collision.h"

enum EnemyAnimationState {
    E_IDLE,
    E_WALKING,
    E_ATTACKING,
};

class Enemy : public Entity, public Animated<EnemyAnimationState>, public Collision {
    private:
        // Variables
        sf::CircleShape _aggroRange;

        // Variables
        float _speed;
        float _hp;
        int _damage;

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
        void updateAnimations();
        void update();
        void render(sf::RenderTarget& target);
};