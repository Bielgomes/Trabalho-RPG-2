#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"

class Player : public Entity {
    private:
        // Variables
        sf::Texture* _texture;
        sf::Sprite* _sprite;

        // Variables
        float _speed;
        float _hp;
        int _xp;

        // Private Functions
        void initVariables();
        void initTexture();
        void initSprite();

    public:
        // Constructor and Destructor
        Player();
        ~Player();

        // Accessors
        const sf::Vector2f& getPosition() const;
        const sf::FloatRect getShape() const;

        // Functions
        void update();
        void render(sf::RenderTarget& target) {
            target.draw(*_sprite);
        };
};