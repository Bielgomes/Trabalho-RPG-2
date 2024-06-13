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
        Sword();
        virtual ~Sword();

        void update(Entity* entity);
        void update();
};