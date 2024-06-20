#pragma once

#include "Animated.hpp"
#include "Enemy.hpp"

enum BigDemonAnimationState {
    BD_IDLE,
    BD_WALKING,
    BD_ATTACKING,
};

class BigDemon : public Enemy, public Animated<BigDemonAnimationState> {
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
        BigDemon();
        BigDemon(float x, float y);
        virtual ~BigDemon();

        // Functions
        void takeDamage(int damage);
        void takeDamage(int damage, sf::Vector2f direction);
        void takeDamage(int damage, CombatEntity* entity, sf::Vector2f direction);

        void updateAnimations();
        void updateMovement();
        void update();

        void listFree();
};