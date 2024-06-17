#include "../headers/TileMapContext.hpp"

#include <iostream>

// Variables
TileMap* TileMapContext::getTileMap(std::string name) {
    return _tileMapContext[name];
}

void TileMapContext::addTileMap(std::string name, TileMap* tileMap) {
    _tileMapContext[name] = tileMap;
}

void TileMapContext::removeTileMap(std::string name) {
    delete _tileMapContext[name];
    _tileMapContext.erase(name);
}

bool TileMapContext::isColliding(std::vector<std::string> name, sf::FloatRect bounds, sf::Vector2f direction) {
    for (auto n : name) {
        if (_tileMapContext[n]->isColliding(bounds, direction)) {
            return true;
        }
    }

    return false;
}

void TileMapContext::updateTileMap(std::string name) {
    _tileMapContext[name]->update();
}

void TileMapContext::renderTileMap(std::string name, sf::RenderTarget& target) {
    _tileMapContext[name]->render(target);
}