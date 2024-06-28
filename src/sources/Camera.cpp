#include "../headers/Camera.hpp"
#include "../headers/Functions.hpp"

// Private Functions
void Camera::initVariables() {
    _entity = nullptr;
    _target = nullptr;
    _camera = nullptr;
}

// Constructor and Destructor
Camera::Camera(sf::RenderTarget* target) {
    initVariables();

    _target = target;
    _camera = new sf::View(sf::FloatRect(0.f, 0.f, 400.f, 225.f));
}

Camera::~Camera() {
    delete _camera;
}

// Accessors
sf::View* Camera::getCamera() const {
    return _camera;
}

// Modifiers
void Camera::bind(Entity* entity) {
    _entity = entity;
}

void Camera::unbind() {
    _entity = nullptr;
}

// Functions
void Camera::update() {
    sf::Vector2f toPosition = _entity->getCenter();
    sf::Vector2f interpolatedPosition = Functions::lerp(toPosition.x, toPosition.y, _camera->getCenter().x, _camera->getCenter().y, 0.15f);

    _camera->setCenter(interpolatedPosition);
    _target->setView(*_camera);
}

void Camera::update(float x, float y) {
    _camera->setCenter(x, y);
    _target->setView(*_camera);
}