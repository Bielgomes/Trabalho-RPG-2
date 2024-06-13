#pragma once

#include "WindowContext.h"
#include "EntityContext.h"
#include "TextureContext.h"

class Context {
    private:
        static WindowContext* _windowContext;
        static EntityContext* _entityContext;
        static TextureContext* _textureContext;

    public:
        Context() = delete;

        static WindowContext* getWindowContext();
        static EntityContext* getEntityContext();
        static TextureContext* getTextureContext();
};