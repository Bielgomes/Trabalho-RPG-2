#pragma once

#include <map>
#include <string>

#include "TileMap.hpp"

class TileMapContext {
    private:
        // Variables
        std::map<std::string, TileMap*> _tileMapContext;

    public:
        // Functions
        TileMap* getTileMap(std::string name);
        void addTileMap(std::string name, TileMap* tileMap);
        void removeTileMap(std::string name);

        bool isColliding(std::string name, sf::FloatRect bounds);

        void updateTileMap(std::string name);
        void renderTileMap(std::string name, sf::RenderTarget& target);
};