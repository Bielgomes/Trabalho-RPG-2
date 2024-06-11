#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity.h"

class Enemy : public Entity {
    private:
        // Variables
        sf::Texture* _texture;
        sf::Sprite* _sprite;

        // Variables
        float _speed;
        float _hp;
        int _damage;

        // Private Functions
        void initVariables();
        void initTexture();
        void initSprite();

    public:
        // Constructor and Destructor
        Enemy();
        virtual ~Enemy();

        // Accessors
        const sf::Vector2f& getPosition() const;
        const sf::FloatRect getShape() const;

        // Functions
        void update();
        void render(sf::RenderTarget& target);
};