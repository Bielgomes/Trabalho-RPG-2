#include "../headers/Context.hpp"
#include "../headers/TileMap.hpp"

// Variables
void TileMap::initVariables() {
    _texture = nullptr;
    _tileSize = 0;
}

// Constructor and Destructor
TileMap::TileMap() {
    initVariables();
}

TileMap::TileMap(sf::Texture* texture, unsigned width, unsigned height, unsigned tileSize) {
    initVariables();

    _texture = texture;
    _tileSize = tileSize;

    _tiles.resize(width);
    for (unsigned i = 0; i < _tiles.size(); i++)
        _tiles[i].resize(height, nullptr);
}

TileMap::~TileMap() {
    for (unsigned i = 0; i < _tiles.size(); i++) {
        for (unsigned j = 0; j < _tiles[i].size(); j++) {
            delete _tiles[i][j];
            _tiles[i][j] = nullptr;
        }
    }

    for (unsigned i = 0; i < _collisions.size(); i++)
        delete _collisions[i];
}

// Functions
void TileMap::addTile(unsigned x, unsigned y, sf::Vector2f position) {
    if (x < _tiles.size() && x >= 0)
        if (y < _tiles[x].size() && y >= 0)
            if (_tiles[x][y] == nullptr)
                _tiles[x][y] = new Tile(x, y, _tileSize, _texture, sf::IntRect(position.x, position.y, _tileSize, _tileSize), false);
}

void TileMap::removeTile(unsigned x, unsigned y) {
    if (x < _tiles.size()) {
        if (y < _tiles[x].size()) {
            if (_tiles[x][y] != nullptr) {
                delete _tiles[x][y];
                _tiles[x][y] = nullptr;
            }
        }
    }
}

bool TileMap::isColliding(sf::FloatRect bound, sf::Vector2f direction) {
    for (auto collision : _collisions) {
        if (collision->getGlobalBounds().intersects(
            sf::FloatRect(bound.left + direction.x, bound.top + direction.y, bound.width, bound.height)
        ))
            return true;
    }

    return false;
}

void TileMap::addCollision(int x, unsigned y, sf::Vector2f position) {
    sf::RectangleShape* collision = new sf::RectangleShape(sf::Vector2f(x, y));
    collision->setPosition(position);
    _collisions.push_back(collision);
}

void TileMap::update() {
    for (unsigned i = 0; i < _tiles.size(); i++)
        for (unsigned j = 0; j < _tiles[i].size(); j++)
            if (_tiles[i][j] != nullptr)
                _tiles[i][j]->update();
}

void TileMap::render(sf::RenderTarget& target) {
    for (unsigned i = 0; i < _tiles.size(); i++)
        for (unsigned j = 0; j < _tiles[i].size(); j++)
            if (_tiles[i][j] != nullptr)
                _tiles[i][j]->render(target);
}