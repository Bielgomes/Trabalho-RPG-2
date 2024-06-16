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
        Player* _player;
        Camera* _camera;

        // Private Functions
        void initVariables();
        void initWindow();
        void initTileMap();
        void initPlayer();

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