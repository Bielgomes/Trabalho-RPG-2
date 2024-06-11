#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Camera.h"
#include "Enemy.h"


class Game {
    private:
        // Window
        sf::RenderWindow* _window;
        sf::Event _event;

        // Player
        Player* _player;
        Camera* _camera;

        // Enemies
        Enemy* _enemy;

        // Private Functions
        void initVariables();
        void initWindow();
        void initPlayer();

    public:
        // Constructor and Destructor
        Game();
        ~Game();

        // Functions
        void run();

        void pollEvents();
        void update();

        void render();
};