#include "../headers/WindowContext.h"

sf::RenderWindow* WindowContext::_window = nullptr;
sf::View* WindowContext::_view = nullptr;

void WindowContext::setWindow(sf::RenderWindow* window) {
    _window = window;
}

sf::RenderWindow* WindowContext::getWindow() {
    return _window;
}

void WindowContext::setView(sf::View* view) {
    _view = view;
}

sf::View* WindowContext::getView() {
    return _view;
}

sf::Vector2f WindowContext::getMousePosition() {
    return _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));
}