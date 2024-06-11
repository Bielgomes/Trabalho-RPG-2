#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"

class Player : public Entity {
    private:
        // Variables
        sf::Texture* _texture;
        sf::Sprite* _sprite;

        sf::RectangleShape _collision;

        // Variables
        float _speed;
        float _hp;
        int _xp;

        // Private Functions
        void initVariables();
        void initSprite();

    public:
        // Constructor and Destructor
        Player(sf::Texture* texture);
        virtual ~Player();

        // Accessors
        const sf::Vector2f& getPosition() const;
        const sf::FloatRect getShape() const;

        // Functions
        void update();
        void render(sf::RenderTarget& target);
};