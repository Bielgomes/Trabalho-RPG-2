#include "../headers/Context.hpp"

#include "../headers/Chest.hpp"

// Private Functions
void Chest::initVariables() {
    _opened = false;
}

void Chest::initTexture() {
    sf::Texture* texture = Context::getTextureContext()->getTexture("OPENNEDCHEST");
    if (texture == nullptr) {
        texture = new sf::Texture();
        if (!texture->loadFromFile("src/resources/textures/opennedChestSprite.png")) {
            std::cout << "ERROR::CHEST::INITTEXTURES::Could not load oppened chest texture file." << "\n";
        }
        Context::getTextureContext()->addTexture("OPENNEDCHEST", texture);

        texture = new sf::Texture();
        if (!texture->loadFromFile("src/resources/textures/closedChestSprite.png")) {
            std::cout << "ERROR::CHEST::INITTEXTURES::Could not load closed chest texture file." << "\n";
        }
        Context::getTextureContext()->addTexture("CLOSEDCHEST", texture);
    }

    _texture = texture;
}

void Chest::initSprite() {
    _sprite = new sf::Sprite();
    _sprite->setTexture(*_texture);
    _sprite->setScale(1.f, 1.f);
}

// Constructor and Destructor
Chest::Chest(sf::Vector2f position) {
    initVariables();
    initTexture();
    initSprite();

    _sprite->setPosition(position);
}

Chest::~Chest() {

}

// Functions
void Chest::update() {
    if (_opened)
        _sprite->setTexture(*Context::getTextureContext()->getTexture("OPENNEDCHEST"));
    else
        _sprite->setTexture(*Context::getTextureContext()->getTexture("CLOSEDCHEST"));
}

void Chest::listFree() {
    Context::getEntityContext()->removeFromGroup("CHESTS", this);
}