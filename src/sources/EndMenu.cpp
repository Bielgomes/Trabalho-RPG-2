#include "../headers/Context.hpp"
#include "../headers/Character.hpp"

#include "../headers/EndMenu.hpp"

// Private Functions
void EndMenu::initVariables()  {
    _isOpen = true;
}

void EndMenu::initBackground()  {

}

void EndMenu::initFont() {
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

void EndMenu::initText() {
    Character *player = (Character*) Context::getEntityContext()->getEntitiesInGroup("CHARACTER")->entity;
    if (player->getHp() <=0) {
        _endText = new sf::Text("You Died!", *_font, 30);
        _endText->setFillColor(sf::Color::Red);
    } else {
        _endText = new sf::Text("You Won!", *_font, 30);
        _endText->setFillColor(sf::Color::Green);
    }

    _scoreText = new sf::Text("Score: 100 Gold", *_font, 20);
    _scoreText->setFillColor(sf::Color::Yellow);

    _endText->setPosition(
        Context::getWindowContext()->getView()->getCenter().x - _endText->getGlobalBounds().width / 2,
        Context::getWindowContext()->getView()->getCenter().y - 50
    );
    _scoreText->setPosition(
        Context::getWindowContext()->getView()->getCenter().x - _scoreText->getGlobalBounds().width / 2,
        Context::getWindowContext()->getView()->getCenter().y + 50
    );
}

// Constructor and Destructor
EndMenu::EndMenu() {
    initVariables();
    initBackground();
    initFont();
    initText();
}

EndMenu::~EndMenu() {
    delete _endText;
    delete _scoreText;
}

// Functions
void EndMenu::update() {

}

void EndMenu::render(sf::RenderTarget& target) {
    target.draw(*_endText);
    target.draw(*_scoreText);
}