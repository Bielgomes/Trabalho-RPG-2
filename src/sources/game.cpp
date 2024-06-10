#include "../headers/Game.h"

// Private Functions
void Game::initVariables() {

}

void Game::initWindow() {
    _window = new sf::RenderWindow(sf::VideoMode(1280, 720), "T2 - RPG", sf::Style::Titlebar | sf::Style::Close);
    _window->setFramerateLimit(60);
    _window->setVerticalSyncEnabled(false);
}

// Constructor and Destructor
Game::Game() {
    initVariables();
    initWindow();
}

Game::~Game() {
    delete _window;
}

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
    
}

void Game::render() {
    _window->clear();
    _window->display();
}
