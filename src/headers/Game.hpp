#pragma once

#include <SFML/Graphics.hpp>

#include "InventoryMenu.hpp"
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

        bool _isRunning;
        bool _gameOver;

        // Player
        Camera* _camera;

        InventoryMenu* _inventory;
        bool _isKeyPressed;

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