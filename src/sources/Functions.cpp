#include <cmath>
#include <algorithm>

#include "../headers/Functions.h"

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

sf::Vector2f Functions::normalize(sf::Vector2f vector) {
    float length = sqrt(vector.x * vector.x + vector.y * vector.y);
    if (length != 0)
        vector /= length;

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