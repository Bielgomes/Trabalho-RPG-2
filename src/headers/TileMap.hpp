#pragma once

#include <vector>

#include "Tile.hpp"

class TileMap {
    private:
        // Variables
        std::vector<std::vector<Tile*>> _tiles;
        std::vector<sf::RectangleShape*> _collisions;
        
        sf::Texture* _texture;
        unsigned _tileSize;

        void initVariables();
        void initTexture();

    public:
        // Constructor and Destructor
        TileMap();
        TileMap(unsigned width, unsigned height, unsigned tileSize);
        virtual ~TileMap();

        // Functions
        void addTile(unsigned x, unsigned y, sf::Vector2f position);
        void removeTile(unsigned x, unsigned y);

        bool isColliding(sf::FloatRect bound, sf::Vector2f direction);
        void addCollision(int x, unsigned y, sf::Vector2f position);

        void update();
        void render(sf::RenderTarget& target);
};