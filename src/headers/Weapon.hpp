#pragma once

#include "CombatEntity.hpp"

class Weapon : public Entity {
    protected:
        std::string _texturePath;
        std::string _textureName;

        // Variables
        CombatEntity* _entity;

        sf::RectangleShape _hitbox;

        sf::Clock _attackTimer;
        bool _isAttacking;
        bool _isAttackButtonPressed;

        int _dmg;

        // Private Functions
        void initVariables();
        void initTexture();
        void initSprite();

    public:
        // Constructor and Destructor
        Weapon(CombatEntity* entity, std::string textureName, std::string texturePath);
        virtual ~Weapon();

        // Functions
        int getDamage();
        bool isAttacking();

        void update();

        void listFree();
};