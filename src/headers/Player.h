#pragma once

#include <SFML/Graphics.hpp>

#include "Animated.h"
#include "CombatEntity.h"
#include "Weapon.h"

enum PlayerAnimationState {
    IDLE,
    WALKING,
};

class Player : public CombatEntity, public Animated<PlayerAnimationState> {
    private:
        // Variables
        std::string name;
        float _speed;
        int _xp;

        Weapon* _weapon;

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
        int getDamage();
        void takeDamage(int damage);
        int getHp();

        void addXp(int xp);
        int getLevel();

        // Inventory things...

        void updateAnimations();
        void update();
        void render(sf::RenderTarget& target);
};