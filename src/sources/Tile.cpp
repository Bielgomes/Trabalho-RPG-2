#include "../headers/Tile.hpp"

// Private Functions
void Tile::initVariables() {
    _texture = nullptr;
    _sprite = nullptr;
    _damaging = false;
}

void Tile::initTexture(sf::Texture* texture) {
    _texture = texture;
}

void Tile::initSprite(unsigned gridX, unsigned gridY, unsigned tileSize, sf::IntRect rect) {
    _sprite = new sf::Sprite();
    _sprite->setTexture(*_texture);
    _sprite->setTextureRect(rect);
    _sprite->setPosition(gridX * tileSize, gridY * tileSize);
}

// Constructor and Destructor
Tile::Tile(unsigned gridX, unsigned gridY, unsigned tileSize, sf::Texture* texture, sf::IntRect rect, bool damaging) {
    initVariables();
    _damaging = damaging;
    initTexture(texture);
    initSprite(gridX, gridY, tileSize, rect);
}

Tile::~Tile() {
    delete _sprite;
}

// Functions
void Tile::update() {}

void Tile::render(sf::RenderTarget& target) {
    target.draw(*_sprite);
}