#pragma once

#include <SFML/Graphics.hpp>

class Menu {
    protected:
        // Variables
        sf::Font* _font;
        sf::RectangleShape _background;

        bool _isOpen;

        virtual void initVariables() = 0;
        virtual void initBackground() = 0;
        virtual void initFont() = 0;
        virtual void initText() = 0;

    public:
        // Functions
        bool isOpen() const;
        void setIsOpen();

        virtual void update() = 0;
        virtual void render(sf::RenderTarget& target) = 0;
};