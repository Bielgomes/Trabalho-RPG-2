#pragma once

#include <SFML/Graphics.hpp>

#include "Animated.hpp"
#include "CombatEntity.hpp"
#include "Weapon.hpp"
#include "Armor.hpp"

enum CharacterAnimationState {
    IDLE,
    WALKING,
    HIT
};

class Character : public CombatEntity, public Animated<CharacterAnimationState> {
    protected:
        // Variables
        std::string _name;
        
        std::string _texturePath;
        std::string _textureName;

        sf::Clock _specialAttackTimer;
        bool _isSpecialAttckButtonPressed;

        Weapon* _weapon;

        // Private Functions
        virtual void initVariables() = 0;
        void initTexture();
        void initSprite();
        void initAnimations();

    public:       
        // Constructor and Destructor
        virtual ~Character();

        // Functions
        int getDamage();
        void takeDamage(int damage, sf::Vector2f direction);
        int getHp();

        void addXp(int xp);
        int getLevel();

        void updateAnimations();
        void updateMovement();
        void update();

        void render(sf::RenderTarget& target);

        void listFree();
};