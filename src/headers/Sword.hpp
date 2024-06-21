#pragma once

#include "Weapon.hpp"
#include "Character.hpp"

class Sword : public Weapon {
    private:
        // Variables
        Character* _entity;

        // Private Functions
        void initVariables();
        void initTexture();
        void initSprite();

    public:
        // Constructor and Destructor
        Sword(Character* entity);
        virtual ~Sword();

        // Functions
        int getDamage();
        bool isAttacking();

        void update();

        void listFree();
};