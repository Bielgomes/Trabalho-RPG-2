#include <iostream>

#include "../headers/Context.hpp"
#include "../headers/Inventory.hpp"

// Constructor and Destructor
Inventory::Inventory()  {
    _overlay.setSize(sf::Vector2f(410.f, 230.f));
    _overlay.setFillColor(sf::Color(20, 20, 20, 200));
    _overlay.setOutlineColor(sf::Color::White);

    _background.setSize(sf::Vector2f(350.f, 200.f));
    _background.setFillColor(sf::Color(20, 20, 20, 255));
    _background.setOutlineColor(sf::Color::White);

    _isOpen = false;
}

Inventory::~Inventory()  {

}

// Functions
bool Inventory::isOpen() const  {
    return _isOpen;
}

void Inventory::setIsOpen() {
    _isOpen = !_isOpen;
}

void Inventory::update() {
    if (!_isOpen)
        return;

    _overlay.setPosition(Context::getWindowContext()->getView()->getCenter().x - _overlay.getSize().x / 2.f, Context::getWindowContext()->getView()->getCenter().y - _overlay.getSize().y / 2.f);
    _background.setPosition(Context::getWindowContext()->getView()->getCenter().x - _background.getSize().x / 2.f, Context::getWindowContext()->getView()->getCenter().y - _background.getSize().y / 2.f);
}

void Inventory::render(sf::RenderTarget& target) {
    if (!_isOpen)
        return;

    target.draw(_overlay);
    target.draw(_background);
}