#include "../headers/Context.hpp"

// Variables
WindowContext* Context::_windowContext = new WindowContext();
EntityContext* Context::_entityContext = new EntityContext();
TextureContext* Context::_textureContext = new TextureContext();
TileMapContext* Context::_tileMapContext = new TileMapContext();
FontContext* Context::_fontContext = new FontContext();

// Destructor
Context::~Context() {
    delete _windowContext;
    delete _entityContext;
    delete _textureContext;
    delete _tileMapContext;
}

// Functions
WindowContext* Context::getWindowContext() {
    return _windowContext;
}

EntityContext* Context::getEntityContext() {
    return _entityContext;
}

TextureContext* Context::getTextureContext() {
    return _textureContext;
}

TileMapContext* Context::getTileMapContext() {
    return _tileMapContext;
}

FontContext* Context::getFontContext() {
    return _fontContext;
}