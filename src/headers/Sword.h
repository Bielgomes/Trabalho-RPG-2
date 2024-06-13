#pragma once

#include "Weapon.h"

class Sword : public Weapon {
    protected:
        // Private Functions
        void initVariables();
        void initTexture();
        void initSprite();

    public:
        // Constructor and Destructor
        Sword(Entity* entity);
        virtual ~Sword();

        // Functions
        int getDamage();

        void update();
        void render(sf::RenderTarget& target);
};