#include "Context.hpp"
#include "Inventory.hpp"

enum Items {
    COIN = 0,
    ELM,
    CHESTPLATE,
    BOOT,
    GLOVE
};

// Private Functions
void Inventory::initVariables() {
    _data = new Item[_capacity];
    _size = 0;
    _start = 0;
    _end = 0;
}

void Inventory::initTextures() {
    sf::Texture* texture = Context::getTextureContext()->getTexture("COIN");
    if (texture == nullptr) {
        texture = new sf::Texture;
        if (!texture->loadFromFile("src/resources/textures/coinSprite.png")) {
            std::cout << "ERROR::INVENTORY::INITTEXTURES::Could not load Coin texture file." << std::endl;
        }
        Context::getTextureContext()->addTexture("COIN", texture);
    }

    texture = Context::getTextureContext()->getTexture("ELM");
    if (texture == nullptr) {
        texture = new sf::Texture;
        if (!texture->loadFromFile("src/resources/textures/elmSprite.png")) {
            std::cout << "ERROR::INVENTORY::INITTEXTURES::Could not load elmSprite texture file." << std::endl;
        }
        Context::getTextureContext()->addTexture("ELM", texture);
    }

    texture = Context::getTextureContext()->getTexture("CHESTPLATE");
    if (texture == nullptr) {
        texture = new sf::Texture;
        if (!texture->loadFromFile("src/resources/textures/chestplateSprite.png")) {
            std::cout << "ERROR::INVENTORY::INITTEXTURES::Could not load chestplateSprite texture file." << std::endl;
        }
        Context::getTextureContext()->addTexture("CHESTPLATE", texture);
    }

    texture = Context::getTextureContext()->getTexture("BOOT");
    if (texture == nullptr) {
        texture = new sf::Texture;
        if (!texture->loadFromFile("src/resources/textures/bootSprite.png")) {
            std::cout << "ERROR::INVENTORY::INITTEXTURES::Could not load bootSprite texture file." << std::endl;
        }
        Context::getTextureContext()->addTexture("BOOT", texture);
    }

    texture = Context::getTextureContext()->getTexture("GLOVE");
    if (texture == nullptr) {
        texture = new sf::Texture;
        if (!texture->loadFromFile("src/resources/textures/gloveSprite.png")) {
            std::cout << "ERROR::INVENTORY::INITTEXTURES::Could not load gloveSprite texture file." << std::endl;
        }
        Context::getTextureContext()->addTexture("GLOVE", texture);
    }

    texture = Context::getTextureContext()->getTexture("FLASK");
    if (texture == nullptr) {
        texture = new sf::Texture;
        if (!texture->loadFromFile("src/resources/textures/flaskSprite.png")) {
            std::cout << "ERROR::INVENTORY::INITTEXTURES::Could not load flaskSprite texture file." << std::endl;
        }
        Context::getTextureContext()->addTexture("FLASK", texture);
    }
}

//Contstructors and Destructors
Inventory::Inventory(unsigned int capacity) {
    _capacity = capacity;

    initVariables();
    initTextures();
}

Inventory::~Inventory() {
    delete[] _data;
}

// Accessors
bool Inventory::isEmpty() const {
    return _size == 0;
}

bool Inventory::isFull() const {
    return _size == _capacity;
}

unsigned int Inventory::getSize() const {
    return _size;
}

unsigned int Inventory::getCapacity() const {
    return _capacity;
}

unsigned int Inventory::getStart() const {
    return _start;
}

unsigned int Inventory::getEnd() const {
    return _end;
}

Item* Inventory::getData() const {
    return _data;
}

// Functions
void Inventory::enqueue(unsigned int id, unsigned int quantity) {
    if (isFull()) {
        std::cout << "ERROR::INVENTORY::ADD::Inventory is full." << std::endl;
        return;
    }

    for (unsigned int i = 0; i < _size; i++) {
        unsigned int index = (_start + i) % _capacity;
        if (_data[index].id == id) {
            _data[index].quantity += quantity;
            return;
        }
    }

    _data[_end].id = id;
    _data[_end].quantity = quantity;

    _end = (_end + 1) % _capacity;
    _size++;
}

void Inventory::dequeue() {
    if (isEmpty()) {
        std::cout << "ERROR::INVENTORY::REMOVE::Inventory is empty." << std::endl;
        return;
    }

    _data[_start].id = -1;
    _data[_start].quantity = 0;
    _start = (_start + 1) % _capacity;
    _size--;
}