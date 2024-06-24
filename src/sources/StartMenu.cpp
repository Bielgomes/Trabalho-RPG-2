#include <iostream>

#include "../headers/StartMenu.hpp"
#include "../headers/Context.hpp"

// Private Functions
void StartMenu::initVariables() {
    _isOpen = true;
    _classIndex = 0;
}

void StartMenu::initBackground() {
    _texture = new sf::Texture();
    if (!_texture->loadFromFile("src/resources/textures/menu.png")) {
        std::cout << "ERROR::STARTMENU::INITBACKGROUND::Could not load start menu background texture file." << std::endl;
    }

    _classRectangles.push_back(new sf::RectangleShape(sf::Vector2f(300, 300)));
    _classRectangles.push_back(new sf::RectangleShape(sf::Vector2f(300, 300)));
    _classRectangles.push_back(new sf::RectangleShape(sf::Vector2f(300, 300)));

    for (int i = 0; i < (int) _classRectangles.size(); i++) {
        _classRectangles[i]->setFillColor(sf::Color::Transparent);
        _classRectangles[i]->setOutlineThickness(2);
        _classRectangles[i]->setPosition(130 + i * 360, 360);
    }

    _sprite = new sf::Sprite(*_texture);
}

void StartMenu::initFont() {
    sf::Font* font = Context::getFontContext()->getFont("DEPIXEL");
    if (font == nullptr) {
        font = new sf::Font();
        if (!font->loadFromFile("src/resources/fonts/DePixel.ttf")) {
            std::cout << "ERROR::STARTMENU::INITTEXT::Could not load start menu font file." << std::endl;
        }
        Context::getFontContext()->addFont("DEPIXEL", font);
    }
    _font = font;
}

void StartMenu::initText() {
    _nameText = new sf::Text();
    _nameText->setFont(*_font);

    _nameText->setCharacterSize(50);
    _nameText->setFillColor(sf::Color::White);
    _nameText->setPosition(
        Context::getWindowContext()->getWindow()->getSize().x / 2 - 100, 200
    );
}

// Constructor and Destructor
StartMenu::StartMenu() {
    initVariables();
    initBackground();
    initFont();
    initText();
}

StartMenu::~StartMenu() {
    delete _sprite;
}

// Accessors
int StartMenu::getClassIndex() const {
    return _classIndex;
}

std::string StartMenu::getName() const {
    return _name;
}

// Functions
void StartMenu::pollEvent(sf::Event::TextEvent* textEvent) {
    // Letters
    if ((textEvent->unicode >= 65 && textEvent->unicode <= 90) || (textEvent->unicode >= 97 && textEvent->unicode <= 122)) {
        if (_name.size() < 15) {
            _name.push_back(static_cast<char>(textEvent->unicode));
            return;
        }
    }

    // Backspace
    if (textEvent->unicode == 8) {
        if (_name.size() > 0) {
            _name.pop_back();
            return;
        }
    }

    // Control + Backspace
    if (textEvent->unicode == 127) {
        _name.clear();
        return;
    }

    // Enter
    if (textEvent->unicode == 13 && _name.size() > 0)
        _isOpen = false;
}

void StartMenu::update() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2f mousePos = Context::getWindowContext()->getMousePosition();
        mousePos = Context::getWindowContext()->getWindow()->mapPixelToCoords(sf::Vector2i(mousePos));

        for (int i = 0; i < (int) _classRectangles.size(); i++) {
            if (_classRectangles[i]->getGlobalBounds().contains(mousePos)) {
                _classIndex = i;
                break;
            }
        }
    }

    for (int i = 0; i < (int) _classRectangles.size(); i++) {
        if (i == _classIndex)
            _classRectangles[i]->setOutlineColor(sf::Color::White);
        else
            _classRectangles[i]->setOutlineColor(sf::Color::Transparent);
    }

    _nameText->setString(_name);
    _nameText->setPosition(
        Context::getWindowContext()->getWindow()->getSize().x / 2 - _nameText->getGlobalBounds().width / 2, 200
    );

    _background.setPosition(130, 360 + _classIndex * 60);
}

void StartMenu::render(sf::RenderTarget& target) {
    target.draw(*_sprite);
    target.draw(*_nameText);

    for (auto rectangle : _classRectangles)
        target.draw(*rectangle);
}
