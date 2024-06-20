#include <iostream>

#include "../headers/Context.hpp"
#include "../headers/InventoryMenu.hpp"

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

// Constructor and Destructor
InventoryMenu::InventoryMenu() {
    initVariables();
    initBackground();
}

InventoryMenu::~InventoryMenu() {}

// Functions
void InventoryMenu::update() {
    if (!_isOpen)
        return;

    _overlay.setPosition(Context::getWindowContext()->getView()->getCenter().x - _overlay.getSize().x / 2.f, Context::getWindowContext()->getView()->getCenter().y - _overlay.getSize().y / 2.f);
    _background.setPosition(Context::getWindowContext()->getView()->getCenter().x - _background.getSize().x / 2.f, Context::getWindowContext()->getView()->getCenter().y - _background.getSize().y / 2.f);
}

void InventoryMenu::render(sf::RenderTarget& target) {
    if (!_isOpen)
        return;

    target.draw(_overlay);
    target.draw(_background);
}