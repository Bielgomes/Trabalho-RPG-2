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
    delete this->window;
}

void Game::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
        }
    }
}

void Game::update()
{
    this->pollEvents();
}

void Game::render()
{
    this->window->clear();

    // Render game

    this->window->display();
}