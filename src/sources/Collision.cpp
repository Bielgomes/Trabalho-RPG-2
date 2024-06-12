#include "../headers/Collision.h"

bool Collision::isColliding(Entity* entity) {
    return _collision.getGlobalBounds().intersects(entity->getShape());
}

bool Collision::isColliding(sf::FloatRect rect) {
    return _collision.getGlobalBounds().intersects(rect);
}

bool Collision::isColliding(sf::CircleShape circle) {
    return _collision.getGlobalBounds().intersects(circle.getGlobalBounds());
}

bool Collision::isColliding(sf::RectangleShape rect) {
    return _collision.getGlobalBounds().intersects(rect.getGlobalBounds());
}