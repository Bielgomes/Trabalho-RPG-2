#pragma once

#include "Weapon.hpp"
#include "Player.hpp"

class Sword : public Weapon {
    private:
        // Variables
        Player* _entity;

        // Private Functions
        void initVariables();
        void initTexture();
        void initSprite();

    public:
        // Constructor and Destructor
        Sword(Player* entity);
        virtual ~Sword();

        // Functions
        int getDamage();
        bool isAttacking();

        void update();
        void render(sf::RenderTarget& target);

        void listFree();
};