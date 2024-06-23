#include "../headers/Context.hpp"
#include "../headers/Game.hpp"

#include "../headers/StartMenu.hpp"
#include "../headers/EndMenu.hpp"

#include "../headers/Demon.hpp"
#include "../headers/BigDemon.hpp"

#include "../headers/CharMage.hpp"
#include "../headers/CharKnight.hpp"
#include "../headers/CharArcher.hpp"

// Private Functions
void Game::initVariables() {
    _window = nullptr;
    _camera = nullptr;

    _isRunning = true;
    _gameOver = false;

    _isKeyPressed = false;
}

void Game::initWindow() {
    sf::Image icon;
    icon.loadFromFile("src/resources/textures/icon.png");

    _window = new sf::RenderWindow(sf::VideoMode(1280, 720), "DunDare", sf::Style::Titlebar | sf::Style::Close);
    _window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    _camera = new Camera(_window);

    Context::getWindowContext()->setWindow(_window);
    Context::getWindowContext()->setView(_camera->getCamera());

    _window->setFramerateLimit(60); 
    _window->setVerticalSyncEnabled(false);
}

void Game::initTileMap() {
    sf::Texture* tilemapTexture = new sf::Texture();
    if (!tilemapTexture->loadFromFile("src/resources/textures/tileMap.png")) {
        std::cout << "ERROR::GAME::INITTEXTURES::Could not load tilemap texture file." << std::endl;
    }
    
    TileMap* tileMap = new TileMap(tilemapTexture, 40, 80, 16);
    Context::getTileMapContext()->addTileMap("BACKGROUND", tileMap);

    const sf::Vector2f GROUND = sf::Vector2f(0, 0);
    const sf::Vector2f GROUND2 = sf::Vector2f(0, 16);
    const sf::Vector2f GROUND3 = sf::Vector2f(0, 32);
    const sf::Vector2f GROUND4 = sf::Vector2f(16, 0);
    const sf::Vector2f GROUND5 = sf::Vector2f(16, 16);
    const sf::Vector2f GROUND6 = sf::Vector2f(16, 32);
    const sf::Vector2f GROUND7 = sf::Vector2f(32, 0);
    const sf::Vector2f GROUND8 = sf::Vector2f(32, 16);

    const sf::Vector2f BOTTOM_LEFT_WALL = sf::Vector2f(133, 288);
    const sf::Vector2f BOTTOM_WALL = sf::Vector2f(150, 288);
    const sf::Vector2f BOTTOM_RIGHT_WALL = sf::Vector2f(171, 288);

    const sf::Vector2f TOP_RIGHT_WALL = sf::Vector2f(43, 123);
    const sf::Vector2f TOP_WALL = sf::Vector2f(149, 219);
    const sf::Vector2f TOP_LEFT_WALL = sf::Vector2f(21, 123);

    const sf::Vector2f RIGHT_WALL = sf::Vector2f(0, 176);
    const sf::Vector2f LEFT_WALL = sf::Vector2f(0, 160);

    // START ROOM
    // WALLS
    tileMap->addTile(0, 0, TOP_LEFT_WALL);
    for (int i = 1; i < 11; i++)
        tileMap->addTile(i, 0, TOP_WALL);
    tileMap->addTile(11, 0, TOP_RIGHT_WALL);

    for (int i = 1; i < 11; i++)
        tileMap->addTile(0, i, LEFT_WALL);

    tileMap->addTile(0, 11, BOTTOM_LEFT_WALL);
    for (int i = 1; i < 11; i++)
        tileMap->addTile(i, 11, BOTTOM_WALL);
    tileMap->addTile(11, 11, BOTTOM_RIGHT_WALL);

    for (int i = 1; i < 4; i++)
        tileMap->addTile(11, i, RIGHT_WALL);
    for (int i = 8; i < 11; i++)
        tileMap->addTile(11, i, RIGHT_WALL); 

    tileMap->addTile(11, 4, TOP_WALL);
    tileMap->addTile(11, 7, BOTTOM_WALL);

    for (int i = 1; i < 11; i++)
        for (int j = 1; j < 11; j++)
            tileMap->addTile(i, j, GROUND); 

    // CORRIDOR
    // WALLS
    tileMap->addTile(11, 5, GROUND);
    tileMap->addTile(11, 6, GROUND);

    for (int i = 12; i < 22; i++) {
        tileMap->addTile(i, 4, TOP_WALL);
        tileMap->addTile(i, 5, GROUND);
        tileMap->addTile(i, 6, GROUND);
        tileMap->addTile(i, 7, BOTTOM_WALL);
    }

    // ROOM 2
    tileMap->addTile(22, 4, TOP_WALL);
    tileMap->addTile(22, 7, BOTTOM_WALL);

    for (int i = 1; i < 4; i++)
        tileMap->addTile(22, i, LEFT_WALL);
    for (int i = 8; i < 11; i++)
        tileMap->addTile(22, i, LEFT_WALL);

    tileMap->addTile(22, 0, TOP_LEFT_WALL);

    for (int i = 23; i < 39; i++)
        tileMap->addTile(i, 0, TOP_WALL);
    
    tileMap->addTile(39, 0, TOP_RIGHT_WALL);

    for (int i = 1; i < 35; i++)
        tileMap->addTile(39, i, RIGHT_WALL);
    for (int i = 11; i < 32; i++)
        tileMap->addTile(22, i, LEFT_WALL);

    tileMap->addTile(39, 35, BOTTOM_RIGHT_WALL);
    tileMap->addTile(22, 32, BOTTOM_LEFT_WALL);

    for (int i = 22; i < 39; i++)
        tileMap->addTile(i, 35, BOTTOM_WALL);

    tileMap->addTile(22, 5, GROUND);
    tileMap->addTile(22, 6, GROUND);

    // GROUND
    for (int i = 23; i < 39; i++)
        for (int j = 1; j < 35; j++)
            tileMap->addTile(i, j, GROUND);

    // ROOM 3
    for (int i = 18; i < 22; i++) {
        tileMap->addTile(i, 32, TOP_WALL);
        tileMap->addTile(i, 33, GROUND);
        tileMap->addTile(i, 34, GROUND);
        tileMap->addTile(i, 35, BOTTOM_WALL);
    }

    tileMap->addTile(22, 33, GROUND);
    tileMap->addTile(22, 34, GROUND);

    tileMap->addTile(17, 32, BOTTOM_RIGHT_WALL);
    tileMap->addTile(17, 35, TOP_RIGHT_WALL);

    for (int i = 25; i < 32; i++)
        tileMap->addTile(17, i, RIGHT_WALL);
    for (int i = 36; i < 44; i++)
        tileMap->addTile(17, i, RIGHT_WALL);

    tileMap->addTile(17, 24, TOP_RIGHT_WALL);
    for (int i = 1; i < 17; i++)
        tileMap->addTile(i, 24, TOP_WALL);

    tileMap->addTile(17, 44, BOTTOM_RIGHT_WALL);
    for (int i = 3; i < 17; i++)
        tileMap->addTile(i, 44, BOTTOM_WALL);

    tileMap->addTile(0, 24, TOP_LEFT_WALL);
    for (int i = 25; i < 79; i++)
        tileMap->addTile(0, i, LEFT_WALL);

    // GROUND
    for (int i = 1; i < 17; i++)
        for (int j = 25; j < 44; j++)
            tileMap->addTile(i, j, GROUND);

    tileMap->addTile(17, 33, GROUND);
    tileMap->addTile(17, 34, GROUND);

    tileMap->addTile(0, 79, BOTTOM_LEFT_WALL);
    for (int i = 1; i < 30; i++)
        tileMap->addTile(i, 79, BOTTOM_WALL);

    tileMap->addTile(30, 79, BOTTOM_RIGHT_WALL);
    for (int i = 45; i < 79; i++)
        tileMap->addTile(30, i, RIGHT_WALL);

    tileMap->addTile(30, 44, TOP_RIGHT_WALL);
    for (int i = 18; i < 30; i++)
        tileMap->addTile(i, 44, TOP_WALL);

    // GROUND
    for (int i = 1; i < 30; i++)
        for (int j = 45; j < 79; j++)
            tileMap->addTile(i, j, GROUND);

    tileMap->addTile(1, 44, GROUND);
    tileMap->addTile(2, 44, GROUND);

    tileMap->addCollision(7, 190, sf::Vector2f(0, 0));
    tileMap->addCollision(183, 10, sf::Vector2f(8, 0));
    tileMap->addCollision(6, 53, sf::Vector2f(185, 11));
    tileMap->addCollision(6, 48, sf::Vector2f(185, 128));
    tileMap->addCollision(183, 10, sf::Vector2f(8, 175));
    tileMap->addCollision(192, 10, sf::Vector2f(175, 64));
    tileMap->addCollision(192, 10, sf::Vector2f(175, 112));
    tileMap->addCollision(6, 62, sf::Vector2f(352, 0));
    tileMap->addCollision(6, 389, sf::Vector2f(352, 123));
    tileMap->addCollision(274, 10, sf::Vector2f(359, 0));
    tileMap->addCollision(6, 576, sf::Vector2f(634, 0));
    tileMap->addCollision(361, 10, sf::Vector2f(272, 560));
    tileMap->addCollision(96, 10, sf::Vector2f(272, 513));
    tileMap->addCollision(6, 128, sf::Vector2f(282, 384));
    tileMap->addCollision(6, 135, sf::Vector2f(282, 568));
    tileMap->addCollision(280, 6, sf::Vector2f(0, 384));
    tileMap->addCollision(6, 874, sf::Vector2f(0, 390));
    tileMap->addCollision(496, 7, sf::Vector2f(0, 1265));
    tileMap->addCollision(8, 560, sf::Vector2f(488, 704));
    tileMap->addCollision(439, 10, sf::Vector2f(48, 704));
}

void Game::initCharacter(int classIndex, std::string name) {
    Context::getEntityContext()->addGroup("CHARACTER");
    Context::getEntityContext()->addGroup("ENEMY");
    Context::getEntityContext()->addGroup("PROJECTILE");
    Context::getEntityContext()->addGroup("WEAPON");
    Context::getEntityContext()->addGroup("WEAPONBOW");

    Character* character = nullptr;

    switch (classIndex) {
        case 0:
            character = new CharKnight(sf::Vector2f(32, 32), name);
            break;
        case 1:
            character = new CharArcher(sf::Vector2f(32, 32), name);
            break;
        case 2:
            character = new CharMage(sf::Vector2f(32, 32), name);
            break;
    }

    Context::getEntityContext()->addToGroup("CHARACTER", character);
    _camera->bind(character);

    _inventory = new InventoryMenu();
}

void Game::initEnemies() {
    Context::getEntityContext()->addGroup("ENEMY");
    Context::getEntityContext()->addGroup("BOSS");

    Context::getEntityContext()->addToGroup("ENEMY", new Demon(319, 95));
    Context::getEntityContext()->addToGroup("ENEMY", new Demon(480, 84));
    Context::getEntityContext()->addToGroup("ENEMY", new Demon(576, 128));
    Context::getEntityContext()->addToGroup("ENEMY", new Demon(431, 223));
    Context::getEntityContext()->addToGroup("ENEMY", new Demon(543, 239));
    Context::getEntityContext()->addToGroup("ENEMY", new Demon(415, 447));
    Context::getEntityContext()->addToGroup("ENEMY", new Demon(559, 384));
    Context::getEntityContext()->addToGroup("ENEMY", new Demon(528, 512));
    Context::getEntityContext()->addToGroup("ENEMY", new Demon(398, 542));
    Context::getEntityContext()->addToGroup("ENEMY", new Demon(303, 543));
    Context::getEntityContext()->addToGroup("ENEMY", new Demon(158, 494));
    Context::getEntityContext()->addToGroup("ENEMY", new Demon(63, 575));
    Context::getEntityContext()->addToGroup("ENEMY", new Demon(223, 670));
    
    Context::getEntityContext()->addToGroup("BOSS", new BigDemon(223, 959));
}

// Constructor and Destructor
Game::Game() {
    initVariables();
    initWindow();

    StartMenu* startMenu = new StartMenu();
    while (startMenu->isOpen()) {
        while (_window->pollEvent(_event))
            if (_event.type == sf::Event::TextEntered)
                startMenu->pollEvent(&_event.text);

        _window->clear();
        startMenu->update();
        startMenu->render(*_window);
        _window->display();
    }

    initTileMap();
    initCharacter(startMenu->getClassIndex(), startMenu->getName());
    initEnemies();

    delete startMenu;
}

Game::~Game() {
    delete _window;
    delete _camera;

    delete _inventory;
}

// Functions
void Game::run() {
    while (_window->isOpen()) {
        pollEvents();

        if (_gameOver == false) {
            update();
            render();
        } else {
            EndMenu* endMenu = new EndMenu();
            while (endMenu->isOpen()) {
                pollEvents();
                
                _window->clear();
                endMenu->update();
                endMenu->render(*_window);
                _window->display();
            }

            delete endMenu;
            _window->close();
        }
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        if (!_isKeyPressed) {
            _isKeyPressed = true;
            _inventory->setIsOpen();
        }
    } else {
        _isKeyPressed = false;
    }

    if (
        Context::getEntityContext()->getEntitiesInGroup("BOSS") == nullptr ||
        static_cast<Character*>(Context::getEntityContext()->getEntitiesInGroup("CHARACTER")->entity)->getHp() <= 0
    ) {
        _gameOver = true;
        return;
    }

    Context::getTileMapContext()->updateTileMap("BACKGROUND");

    Context::getEntityContext()->updateGroup("CHARACTER");
    
    Context::getEntityContext()->updateGroup("ENEMY");
    Context::getEntityContext()->updateGroup("BOSS");

    Context::getEntityContext()->updateGroup("PROJECTILE");

    _camera->update();
    _inventory->update();
}

void Game::render() {
    _window->clear();

    Context::getTileMapContext()->renderTileMap("BACKGROUND", *_window);

    Context::getEntityContext()->renderGroup("CHARACTER", *_window);

    Context::getEntityContext()->renderGroup("ENEMY", *_window);
    Context::getEntityContext()->renderGroup("BOSS", *_window);

    Context::getEntityContext()->renderGroup("PROJECTILE", *_window);

    _inventory->render(*_window);

    _window->display();
}
