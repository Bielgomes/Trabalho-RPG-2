#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"

class Camera {
    private:
        // Camera
        sf::View* _camera;
        Entity* _entity;

        sf::RenderTarget* _target;

        // Private Functions
        void initVariables();

    public:
        // Constructor and Destructor
        Camera(sf::RenderTarget* target);
        virtual ~Camera();

        // Accessors
        const sf::View& getCamera() const;

        // Modifiers
        void bind(Entity* entity);
        void unbind();

        // Functions
        void update();
        void update(float x, float y);
};