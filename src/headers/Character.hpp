#pragma once

#include <SFML/Graphics.hpp>

#include "Animated.hpp"
#include "CombatEntity.hpp"
#include "Weapon.hpp"

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
        void initVariables();
        void initTexture();
        void initSprite();
        void initAnimations();

    public:       
        // Constructor and Destructor
        Character(sf::Vector2f position, std::string textureName, std::string texturePath);
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