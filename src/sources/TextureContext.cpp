#include "../headers/TextureContext.h"

sf::Texture* TextureContext::getTexture(std::string name) {
    if (_textureContext.find(name) != _textureContext.end())
        return _textureContext[name];

    return nullptr;
};

void TextureContext::addTexture(std::string name, sf::Texture* texture) {
    _textureContext[name] = texture;
};

void TextureContext::removeTexture(std::string name) {
    if (_textureContext.find(name) != _textureContext.end())
        _textureContext.erase(name);
};