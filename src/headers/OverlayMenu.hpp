#pragma once

#include <SFML/Graphics.hpp>

#include "Menu.hpp"

class OverlayMenu : public Menu {
    protected:
        // Variables
        sf::RectangleShape _overlay;
};