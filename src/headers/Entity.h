#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Entity {
    protected:
        // Variables
        sf::Texture* _texture;
        sf::Sprite* _sprite;

        bool _flip;

        // Private Functions
        virtual void initVariables() = 0;
        virtual void initTexture() = 0;
        virtual void initSprite() = 0;

    public:
        // Accessors
        const sf::Vector2f& getPosition() const;
        const sf::FloatRect getShape() const;

        // Functions
        virtual void update() = 0;
        virtual void render(sf::RenderTarget& target);
};