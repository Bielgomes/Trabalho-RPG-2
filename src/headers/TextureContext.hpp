#pragma once

#include <map>

#include <SFML/Graphics.hpp>

class TextureContext {
    private:
        // Variables
        std::map<std::string, sf::Texture*> _textureContext;

    public:
        // Functions
        sf::Texture* getTexture(std::string name);
        void addTexture(std::string name, sf::Texture* texture);
        void removeTexture(std::string name);
};