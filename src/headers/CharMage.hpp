#pragma once

#include "Character.hpp"

class CharMage : public Character {
    private:
        // Private Functions
        void initVariables();

    public:
        // Constructor and Destructor
        CharMage(sf::Vector2f position, std::string name);
        ~CharMage() = default;

        // Functions
        void update();
};
