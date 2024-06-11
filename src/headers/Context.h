#pragma once

#include "EntityContext.h"
#include "TextureContext.h"

class Context {
    private:
        static EntityContext* _entityContext;
        static TextureContext* _textureContext;

    public:
        Context() = delete;

        static EntityContext* getEntityContext();
        static TextureContext* getTextureContext();
};