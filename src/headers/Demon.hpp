#pragma once

#include "Animated.hpp"
#include "Enemy.hpp"

enum EnemyAnimationState {
    E_IDLE,
    E_WALKING,
    E_ATTACKING,
};

class Demon : public Enemy, public Animated<EnemyAnimationState> {
    private:
        // Variables
        sf::CircleShape _aggroRange;

        // Private Functions
        void initVariables();
        void initTexture();
        void initSprite();
        void initAnimations();

        void applyBleeding();

    public:
        // Constructor and Destructor
        Demon();
        Demon(float x, float y);
        virtual ~Demon();

        // Functions
        void takeDamage(int damage);
        void takeDamage(int damage, sf::Vector2f direction);
        void takeDamage(int damage, CombatEntity* entity, sf::Vector2f direction);

        void updateAnimations();
        void updateMovement();
        void update();

        void listFree();
};