#pragma once

#include <SFML/Graphics.hpp>

class Tile {
    private:
        // Variables
        sf::Texture* _texture;
        sf::Sprite* _sprite;

        bool _damaging;

        // Private Functions
        void initVariables();
        void initTexture(sf::Texture* texture);
        void initSprite(unsigned gridX, unsigned gridY, unsigned tileSize, sf::IntRect rect);

    public:
        // Constructor and Destructor
        Tile(const unsigned gridX, const unsigned gridY, const unsigned tileSize, sf::Texture* texture, sf::IntRect rect, bool damaging = false);
        virtual ~Tile();

        void update();
        void render(sf::RenderTarget& target);
};