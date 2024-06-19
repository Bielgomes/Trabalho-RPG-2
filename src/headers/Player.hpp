#pragma once

#include <SFML/Graphics.hpp>

#include "Animated.hpp"
#include "CombatEntity.hpp"
#include "Weapon.hpp"

enum PlayerAnimationState {
    IDLE,
    WALKING,
};

class Player : public CombatEntity, public Animated<PlayerAnimationState> {
    private:
        // Variables
        std::string name;
        int _xp;

        sf::Clock _specialAttackTimer;
        bool _isSpecialAttckButtonPressed;

        sf::Vector2f _velocity;
        float _velocityMax;
        float _velocityAceleration;
        float _velocityDesaceleration;

        Weapon* _weapon;

        // Private Functions
        void initVariables();
        void initTexture();
        void initSprite();
        void initAnimations();

    public:
        // Constructor and Destructor
        Player(sf::Vector2f position);
        virtual ~Player();
        
        // Functions
        int getDamage();
        void takeDamage(int damage);
        int getHp();

        void addXp(int xp);
        int getLevel();

        // Inventory things...

        void updateAnimations();
        void updateMovement();
        void update();
        
        void render(sf::RenderTarget& target);

        void listFree();
};