#include "game.h"

// Accessors
bool Game::isRunning()
{
    return this->window->isOpen();
}

// Constructor and Destructor
Game::Game()
{
    this->videoMode.width = 1280;
    this->videoMode.height = 720;

    this->window = new sf::RenderWindow(this->videoMode, "RPG", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}

Game::~Game()
{
    this->window->close();
    delete this->window;
}

void Game::update()
{

}

void Game::render()
{

}