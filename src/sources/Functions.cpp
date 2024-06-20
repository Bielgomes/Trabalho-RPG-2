#include <cmath>
#include <algorithm>

#include "../headers/Functions.hpp"

// Functions
float Functions::lerp(float to, float from, float porcentage) {
    return from + (to - from) * porcentage;
}

sf::Vector2f Functions::lerp(float to_x, float to_y, float from_x, float from_y, float porcentage) {
    float x = lerp(to_x, from_x, porcentage);
    float y = lerp(to_y, from_y, porcentage);
    return sf::Vector2f(x, y);
}

sf::Vector2f Functions::lerp(sf::Vector2f to, sf::Vector2f from, float porcentage) {
    float x = lerp(to.x, from.x, porcentage);
    float y = lerp(to.y, from.y, porcentage);
    return sf::Vector2f(x, y);
}

float Functions::vectorMagnitude(sf::Vector2f vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f Functions::normalize(sf::Vector2f vector) {
    float magnitude = vectorMagnitude(vector);
    if (magnitude != 0)
        vector /= magnitude;

    return vector;
}

float Functions::clamp(float value, float min, float max) {
    return std::max(min, std::min(value, max));
}

sf::Vector2f Functions::clamp(sf::Vector2f vector, float min, float max) {
    float x = clamp(vector.x, min, max);
    float y = clamp(vector.y, min, max);
    return sf::Vector2f(x, y);
}

sf::Vector2f Functions::clamp(sf::Vector2f vector, sf::Vector2f min, sf::Vector2f max) {
    float x = clamp(vector.x, min.x, max.x);
    float y = clamp(vector.y, min.y, max.y);
    return sf::Vector2f(x, y);
}

float Functions::angleToDegree(float angle) {
    return angle * 180 / PI;
}

float Functions::pointDirection(float from_x, float from_y, float to_x, float to_y) {
    return atan2(to_y - from_y, to_x - from_x);
}

float Functions::pointDirection(sf::Vector2f from, sf::Vector2f to) {
    return pointDirection(from.x, from.y, to.x, to.y);
}

sf::Vector2f Functions::directionTo(float angle) {
    return sf::Vector2f(cos(angle), sin(angle));
}

sf::Vector2f Functions::directionTo(sf::Vector2f from, sf::Vector2f to) {
    return normalize(to - from);
}

sf::Vector2f Functions::directionTo(float from_x, float from_y, float to_x, float to_y) {
    return directionTo(sf::Vector2f(from_x, from_y), sf::Vector2f(to_x, to_y));
}