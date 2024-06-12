#pragma once

#include "Entity.h"

class Collision {
    protected:
        // Variables
        sf::RectangleShape _collision;

    public:
        // Private Functions
        bool isColliding(Entity* entity);
        bool isColliding(sf::FloatRect rect);
        bool isColliding(sf::CircleShape circle);
        bool isColliding(sf::RectangleShape rect);
};