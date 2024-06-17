#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Animated.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

enum EnemyAnimationState {
    E_IDLE,
    E_WALKING,
    E_ATTACKING,
};

class Demon : public Enemy, public Animated<EnemyAnimationState> {
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

        void applyBleeding();

    public:
        // Constructor and Destructor
        Demon();
        Demon(float x, float y);
        virtual ~Demon();

        // Functions
        int getDamage();
        void takeDamage(int damage);
        void takeDamage(int damage, Player* player);
        int getHp();

        void updateAnimations();
        void update();
        void render(sf::RenderTarget& target);

        void listFree();
};