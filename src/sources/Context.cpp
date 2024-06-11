#include "../headers/Context.h"

EntityContext* Context::_entityContext = new EntityContext();
TextureContext* Context::_textureContext = new TextureContext();

EntityContext* Context::getEntityContext() {
    return _entityContext;
};

TextureContext* Context::getTextureContext() {
    return _textureContext;
};