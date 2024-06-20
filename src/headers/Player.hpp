#pragma once

#include <SFML/Graphics.hpp>

#include "Animated.hpp"
#include "CombatEntity.hpp"
#include "Weapon.hpp"

enum PlayerAnimationState {
    IDLE,
    WALKING,
    HIT
};

class Player : public CombatEntity, public Animated<PlayerAnimationState> {
    private:
        // Variables
        std::string name;
        
        sf::Clock _specialAttackTimer;
        sf::Clock _invencibilityTimer;
        bool _isSpecialAttckButtonPressed;

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
        void takeDamage(int damage, sf::Vector2f direction);
        int getHp();

        void addXp(int xp);
        int getLevel();

        void updateAnimations();
        void updatePhysics();
        void updateMovement();
        void update();
        
        void render(sf::RenderTarget& target);

        void listFree();
};