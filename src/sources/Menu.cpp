#include "../headers/Menu.hpp"

// Functions
bool Menu::isOpen() const  {
    return _isOpen;
}

void Menu::setIsOpen() {
    _isOpen = !_isOpen;
}