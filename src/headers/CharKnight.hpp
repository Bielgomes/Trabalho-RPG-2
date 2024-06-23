#pragma once

#include "Character.hpp"

class CharKnight : public Character {
    private:
        // Private Functions
        void initVariables();

    public:
        // Constructor and Destructor
        CharKnight(sf::Vector2f position, std::string name);
        ~CharKnight() = default;

        // Functions
        void update();
};
