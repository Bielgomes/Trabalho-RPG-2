#include "../headers/Context.h"

EntityContext::EntityContext() {
    _entities = new std::map<std::string, LinkedList>;
}

EntityContext::~EntityContext() {
    for (auto const& x : _entities)
        delete x.second;
}

LinkedList EntityContext::get_entities(std::string key) {
    return _entities[key];
};

void EntityContext::add_entities(std::string key, Entity* entity) {
    if (_entities[key] == nullptr) {
        _entities[key] = new LinkedList();
    }
    _entities[key].add(entity);
};

void EntityContext::remove_entities(std::string key, Entity* entity) {
    if (_entities[key] != nullptr) {
        _entities[key].remove(entity);
    }
};

TextureContext::TextureContext() {
    _textures = new std::map<std::string, sf::Texture*>;
}

TextureContext::~TextureContext() {
    for (auto const& x : _textures) {
        delete x.second;
    }
}

sf::Texture* TextureContext::get_texture(std::string key) {
    return *_textures[key];
};

void TextureContext::add_texture(std::string key, sf::Texture* texture) {
    _textures[key] = texture;
};

void TextureContext::remove_texture(std::string key, sf::Texture* texture) {
    _textures.erase(key);
};