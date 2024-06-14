#include "../headers/Context.h"

// Variables
WindowContext* Context::_windowContext = new WindowContext();
EntityContext* Context::_entityContext = new EntityContext();
TextureContext* Context::_textureContext = new TextureContext();

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