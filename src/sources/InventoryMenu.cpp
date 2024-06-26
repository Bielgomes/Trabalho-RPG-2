#include <iostream>

#include "../headers/Context.hpp"
#include "../headers/InventoryMenu.hpp"
#include "../headers/Character.hpp"

const std::string ItemsNames[] = {
    "Coin",
    "Elm",
    "Chestplate",
    "Boot",
    "Glove",
    "Flask"
};

const std::string ItemsTextures[] = {
    "COIN",
    "ELM",
    "CHESTPLATE",
    "BOOT",
    "GLOVE",
    "FLASK"
};

// Private Functions
void InventoryMenu::initVariables() {
    _isOpen = false;
}

void InventoryMenu::initBackground() {
    _overlay.setSize(sf::Vector2f(410.f, 230.f));
    _overlay.setFillColor(sf::Color(20, 20, 20, 200));

    _background.setSize(sf::Vector2f(350.f, 200.f));
    _background.setFillColor(sf::Color(20, 20, 20, 255));
}

void InventoryMenu::initFont() {
    sf::Font* font = Context::getFontContext()->getFont("DEPIXEL");
    if (font == nullptr) {
        font = new sf::Font();
        if (!font->loadFromFile("src/resources/fonts/DePixel.ttf")) {
            std::cout << "ERROR::INVENTORYMENU::INITTEXT::Could not load inventory menu font file." << std::endl;
        }
        Context::getFontContext()->addFont("DEPIXEL", font);
    }
    font->setSmooth(false);
    _font = font;
}

void InventoryMenu::initText() {
    _characterName = new sf::Text();
    _characterLevel = new sf::Text();

    _characterName->setFont(*_font);
    _characterName->setCharacterSize(12);
    _characterName->setFillColor(sf::Color::White);
    _characterName->setString(
        static_cast<Character*>(
            Context::getEntityContext()->getEntitiesInGroup("CHARACTER")->entity
        )->getName()
    );
    
    _characterLevel->setFont(*_font);
    _characterLevel->setCharacterSize(10);
    _characterLevel->setFillColor(sf::Color::White);
    _characterLevel->setString(
        "Level: " + std::to_string(
            static_cast<Character*>(
                Context::getEntityContext()->getEntitiesInGroup("CHARACTER")->entity
            )->getLevel() + 1
        )
    );
}

// Constructor and Destructor
InventoryMenu::InventoryMenu() {
    initVariables();
    initBackground();
    initFont();
    initText();
}

InventoryMenu::~InventoryMenu() {
    delete _characterName;
    delete _characterLevel;
}

// Functions
void InventoryMenu::update() {
    if (!_isOpen)
        return;

    _overlay.setPosition(
        Context::getWindowContext()->getView()->getCenter().x - _overlay.getSize().x / 2.f,
        Context::getWindowContext()->getView()->getCenter().y - _overlay.getSize().y / 2.f
    );
    _background.setPosition(
        Context::getWindowContext()->getView()->getCenter().x - _background.getSize().x / 2.f,
        Context::getWindowContext()->getView()->getCenter().y - _background.getSize().y / 2.f
    );

    // Top Left corner in _background
    _characterName->setPosition(
        Context::getWindowContext()->getView()->getCenter().x - _background.getSize().x / 2.f + 10.f,
        Context::getWindowContext()->getView()->getCenter().y - _background.getSize().y / 2.f + 10.f
    );
    _characterLevel->setPosition(
        Context::getWindowContext()->getView()->getCenter().x - _background.getSize().x / 2.f + 10.f,
        Context::getWindowContext()->getView()->getCenter().y - _background.getSize().y / 2.f + 30.f
    );
    _characterLevel->setString(
        "Level: " + std::to_string(
            static_cast<Character*>(
                Context::getEntityContext()->getEntitiesInGroup("CHARACTER")->entity
            )->getLevel() + 1
        )
    );
}

void InventoryMenu::render(sf::RenderTarget& target) {
    if (!_isOpen)
        return;

    target.draw(_overlay);
    target.draw(_background);

    target.draw(*_characterName);
    target.draw(*_characterLevel);

    sf::RectangleShape item;
    item.setSize(sf::Vector2f(60.f, 60.f));
    item.setFillColor(sf::Color::Transparent);

    sf::Sprite sprite;
    sprite.setScale(2.f, 2.f);

    sf::Text text;
    text.setFont(*_font);

    Character* character = static_cast<Character*>(Context::getEntityContext()->getEntitiesInGroup("CHARACTER")->entity);
    Inventory* inventory = character->getInventory();

    for (unsigned int i = inventory->getStart(); i < inventory->getEnd(); i = (i + 1) % inventory->getCapacity()) {
        item.setPosition(
            Context::getWindowContext()->getView()->getCenter().x - _background.getSize().x / 2.f + 10.f + (i % 4) * 70.f,
            Context::getWindowContext()->getView()->getCenter().y - _background.getSize().y / 2.f + 50.f + (i / 4) * 70.f
        );
        sprite.setTexture(*Context::getTextureContext()->getTexture(ItemsTextures[inventory->getData()[i].id]));
        sprite.setPosition(
            item.getPosition().x + 5.f,
            item.getPosition().y + 5.f
        );

        text.setPosition(
            item.getPosition().x + 5.f,
            item.getPosition().y + 45.f
        );
        text.setCharacterSize(8);
        text.setFillColor(sf::Color::White);
        text.setString(ItemsNames[inventory->getData()[i].id] + " x" + std::to_string(inventory->getData()[i].quantity));

        target.draw(item);
        target.draw(sprite);
        target.draw(text);
    }
}