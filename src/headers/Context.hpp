#pragma once

#include "WindowContext.hpp"
#include "EntityContext.hpp"
#include "TextureContext.hpp"
#include "TileMapContext.hpp"

class Context {
    private:
        static WindowContext* _windowContext;
        static EntityContext* _entityContext;
        static TextureContext* _textureContext;
        static TileMapContext* _tileMapContext;

    public:
        Context() = delete;
        virtual ~Context();

        static WindowContext* getWindowContext();
        static EntityContext* getEntityContext();
        static TextureContext* getTextureContext();
        static TileMapContext* getTileMapContext();
};