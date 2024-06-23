#pragma once

#include "Character.hpp"

class CharArcher : public Character {
    private:
        // Private Functions
        void initVariables();
        
    public:
        // Constructor and Destructor
        CharArcher(sf::Vector2f position, std::string name);
        ~CharArcher() = default;

        // Functions
        void update();
};
