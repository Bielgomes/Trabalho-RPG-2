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
        float _specialAttackTimerMax;
        bool _isSpecialAttckButtonPressed;

        int _hpMax;

        Weapon* _weapon;

        sf::Text* _specialAttackText;

        // Private Functions
        virtual void initVariables() = 0;
        void initTexture();
        void initSprite();
        void initText();
        void initAnimations();

    public:       
        // Constructor and Destructor
        virtual ~Character();

        // Functions
        int getDamage();
        void takeDamage(int damage, sf::Vector2f direction);
        int getHp();
        std::string getName();

        void addXp(int xp);
        int getLevel();
        
        void updateAnimations();
        void updateMovement();

        virtual void update() = 0;

        void render(sf::RenderTarget& target);

        void listFree();
};