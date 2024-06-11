#include "../headers/Game.h"

// Private Functions
void Game::initVariables() {
    _window = nullptr;
    _camera = nullptr;
    _player = nullptr;

    _enemy = nullptr;
}

void Game::initWindow() {
    _window = new sf::RenderWindow(sf::VideoMode(1280, 720), "T2 - RPG", sf::Style::Titlebar | sf::Style::Close);
    _camera = new Camera(_window);

    _window->setFramerateLimit(60); 
    _window->setVerticalSyncEnabled(false);
}

void Game::initPlayer() {
    _player = new Player();
    _camera->bind(_player);

    _enemy = new Enemy();
}

// Constructor and Destructor
Game::Game() {
    initVariables();
    initWindow();
    initPlayer();
}

Game::~Game() {
    delete _window;
    delete _player;
    delete _camera;
}

// Functions
void Game::run() {
    while (_window->isOpen()) {
        pollEvents();
        update();
        render();
    }
}

void Game::pollEvents() {
    while (_window->pollEvent(_event)) {
        switch (_event.type) {
            case sf::Event::Closed:
                _window->close();
                break;
        }
    }
}

void Game::update() {
    _player->update();
    _camera->update();

    _enemy->update();
}

void Game::render() {
    _window->clear();

    _player->render(*_window);
    _enemy->render(*_window);

    _window->display();
}
