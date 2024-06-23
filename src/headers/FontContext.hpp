#pragma once

#include <map>

#include <SFML/Graphics.hpp>

class FontContext {
    private:
        // Variables
        std::map<std::string, sf::Font*> _fontContext;

    public:
        // Functions
        sf::Font* getFont(std::string name);
        void addFont(std::string name, sf::Font* texture);
        void removeFont(std::string name);
};