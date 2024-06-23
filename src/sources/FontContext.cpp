#include "../headers/FontContext.hpp"

// Functions
sf::Font* FontContext::getFont(std::string name) {
    if (_fontContext.find(name) != _fontContext.end())
        return _fontContext[name];

    return nullptr;
}

void FontContext::addFont(std::string name, sf::Font* font) {
    _fontContext[name] = font;
}

void FontContext::removeFont(std::string name) {
    delete _fontContext[name];
    _fontContext.erase(name);
}