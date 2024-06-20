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
        // Constructor and Destructor
        virtual ~Entity() = default;

        // Accessors
        const sf::Vector2f& getPosition() const;
        const sf::FloatRect getShape() const;
        const sf::Vector2f getCenter() const;

        // Functions
        sf::Vector2f directionTo(Entity* entity);
        sf::Vector2f directionTo(sf::Vector2f target);
        sf::Vector2f directionTo(float x, float y);

        virtual void listFree() = 0;

        virtual void update() = 0;
        virtual void render(sf::RenderTarget& target);
};