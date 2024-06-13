#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Animated.h"
#include "Collision.h"

#include "Weapon.h"

enum PlayerAnimationState {
    IDLE,
    WALKING,
};

class Player : public Entity, public Animated<PlayerAnimationState>, public Collision {
    private:
        // Variables
        std::string name;

        float _speed;
        float _hp;
        int _xp;

        Weapon* _sword;

        // Private Functions
        void initVariables();
        void initTexture();
        void initSprite();
        void initAnimations();

    public:
        // Constructor and Destructor
        Player();
        virtual ~Player();

        // Functions
        void updateAnimations();
        void update();
        void render(sf::RenderTarget& target);
};