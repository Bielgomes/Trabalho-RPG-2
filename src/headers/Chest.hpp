#pragma once

#include "Entity.hpp"

class Chest : public Entity {
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
        void update();
        void render(sf::RenderTarget* target);

        void listFree();
};