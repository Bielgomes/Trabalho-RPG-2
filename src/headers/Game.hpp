#pragma once

#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Camera.hpp"

#include "TileMap.hpp"

class Game {
    private:
        // Window
        sf::RenderWindow* _window;
        sf::Event _event;

        sf::Texture _tileSheet;
        TileMap* _tileMap;

        // Player
        Camera* _camera;

        // Private Functions
        void initVariables();
        void initWindow();
        void initTileMap();
        void initPlayer();
        void initEnemies();

    public:
        // Constructor and Destructor
        Game();
        virtual ~Game();

        // Functions
        void run();

        void pollEvents();
        void update();

        void render();
};