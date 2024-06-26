#pragma once

#include "Collision.hpp"
#include "Entity.hpp"

class Chest : public Entity, public Collision {
    private:
        // Variables
        bool _opened;

        // Private Functions
        void initVariables();
        void initTexture();
        void initSprite();

    public:
        Chest(sf::Vector2f position);
        virtual ~Chest();

        // Functions
        void open();
        void update();

        void listFree();
};