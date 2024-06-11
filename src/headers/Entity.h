#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Entity {
    private:
        // Variables
        sf::Texture* _texture;
        sf::Sprite* _sprite;

        // Private Functions
        virtual void initVariables() = 0;
        virtual void initTexture() = 0;
        virtual void initSprite() = 0;

    public:
        // Accessors
        virtual const sf::Vector2f& getPosition() const = 0;
        virtual const sf::FloatRect getShape() const = 0;

        // Functions
        virtual void update() = 0;
        void render(sf::RenderTarget& target) {
            target.draw(*_sprite);
        };
};