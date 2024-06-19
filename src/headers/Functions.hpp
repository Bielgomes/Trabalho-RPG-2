#pragma once

#include <SFML/Graphics.hpp>

class Functions {
    public:
        // Constants
        static constexpr float PI = 3.14159265359f;

        // Functions
        static float lerp(float to, float from, float porcentage);
        static sf::Vector2f lerp(float to_x, float to_y, float from_x, float from_y, float porcentage);
        static sf::Vector2f lerp(sf::Vector2f to, sf::Vector2f from, float porcentage);

        static float clamp(float value, float min, float max);
        static sf::Vector2f clamp(sf::Vector2f vector, float min, float max);
        static sf::Vector2f clamp(sf::Vector2f vector, sf::Vector2f min, sf::Vector2f max);

        static sf::Vector2f normalize(sf::Vector2f vector);
};