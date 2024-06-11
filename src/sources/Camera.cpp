#include "../headers/Camera.h"

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
const sf::View& Camera::getCamera() const {
    return *_camera;
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
    _camera->setCenter(_entity->getShape().left + _entity->getShape().width / 2, _entity->getShape().top + _entity->getShape().height / 2);
    _target->setView(*_camera);
}

void Camera::update(float x, float y) {
    _camera->setCenter(x, y);
    _target->setView(*_camera);
}