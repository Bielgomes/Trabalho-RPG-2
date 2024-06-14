#include "../headers/Game.h"

#include "../headers/Context.h"

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

    Context::getWindowContext()->setWindow(_window);
    Context::getWindowContext()->setView(_camera->getCamera());

    _window->setFramerateLimit(60); 
    _window->setVerticalSyncEnabled(false);
}

void Game::initPlayer() {
    Context::getEntityContext()->addGroup("PLAYER");
    Context::getEntityContext()->addGroup("ENEMY");

    _player = new Player();
    Context::getEntityContext()->addToGroup("PLAYER", _player);

    _camera->bind(_player);

    _enemy = new Enemy();
    Context::getEntityContext()->addToGroup("ENEMY", _enemy);
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
    delete _enemy;
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
    Context::getEntityContext()->updateGroup("PLAYER");
    Context::getEntityContext()->updateGroup("ENEMY");
    
    _camera->update();
}

void Game::render() {
    _window->clear();

    Context::getEntityContext()->renderGroup("ENEMY", *_window);
    Context::getEntityContext()->renderGroup("PLAYER", *_window);

    _window->display();
}
