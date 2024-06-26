#include "../headers/Context.hpp"

#include "../headers/Chest.hpp"
#include "../headers/Inventory.hpp"
#include "../headers/Character.hpp"

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
    _collision.setPosition(_sprite->getPosition());
    _collision.setSize(sf::Vector2f(16, 16));
    _collision.setFillColor(sf::Color::Transparent);
}

Chest::~Chest() {
    delete _sprite;
}

// Functions
void Chest::open() {
    if (_opened)
        return;

    _opened = true;

    Character* character = static_cast<Character*>(Context::getEntityContext()->getEntitiesInGroup("CHARACTER")->entity);
    Inventory* Inventory = character->getInventory();
    Inventory->enqueue(rand() % 4 + 1, 1);

    character->getArmorStack()->push(1);
}

void Chest::update() {
    if (_opened)
        _sprite->setTexture(*Context::getTextureContext()->getTexture("OPENNEDCHEST"));
    else
        _sprite->setTexture(*Context::getTextureContext()->getTexture("CLOSEDCHEST"));
}

void Chest::listFree() {
    Context::getEntityContext()->removeFromGroup("CHESTS", this);
}