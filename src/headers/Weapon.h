#pragma once

#include "Entity.h"

class Weapon : public Entity {
    protected:
        // Variables
        sf::RectangleShape _hitbox;

    public:
        // Functions
        virtual void update(Entity* entity) = 0;
};