#include "../headers/Game.h"

#include "../headers/Context.h"

// Private Functions
void Game::initVariables() {
    _window = nullptr;
    _camera = nullptr;
    _player = nullptr;

    _enemy = nullptr;
}

void Game::initTextures() {
    sf::Texture* playerTexture = new sf::Texture();
    if (!playerTexture->loadFromFile("src/resources/textures/player.png")) {
        std::cout << "ERROR::GAME::INITTEXTURES::Could not load player texture file." << std::endl;
    }
    Context::getTextureContext()->addTexture("PLAYER", playerTexture);

    sf::Texture* skeletonTexture = new sf::Texture();
    if (!skeletonTexture->loadFromFile("src/resources/textures/skeleton.png")) {
        std::cout << "ERROR::GAME::INITTEXTURES::Could not load skeleton texture file." << std::endl;
    }
    Context::getTextureContext()->addTexture("SKELETON", skeletonTexture);
}

void Game::initWindow() {
    _window = new sf::RenderWindow(sf::VideoMode(1280, 720), "T2 - RPG", sf::Style::Titlebar | sf::Style::Close);
    _camera = new Camera(_window);

    _window->setFramerateLimit(60); 
    _window->setVerticalSyncEnabled(false);
}

void Game::initPlayer() {
    Context::getEntityContext()->addGroup("PLAYER");
    Context::getEntityContext()->addGroup("ENEMY");

    _player = new Player(Context::getTextureContext()->getTexture("PLAYER"));
    Context::getEntityContext()->addToGroup("PLAYER", _player);

    _camera->bind(_player);

    _enemy = new Enemy(Context::getTextureContext()->getTexture("SKELETON"));
    Context::getEntityContext()->addToGroup("ENEMY", _enemy);
}

// Constructor and Destructor
Game::Game() {
    initVariables();
    initTextures();
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
    _player->update();
    _camera->update();

    _enemy->update();
}

void Game::render() {
    _window->clear();

    Context::getEntityContext()->renderGroup("ENEMY", *_window);
    Context::getEntityContext()->renderGroup("PLAYER", *_window);

    _window->display();
}
