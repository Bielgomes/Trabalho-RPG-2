#pragma once

#include "Context.hpp"
#include "Menu.hpp"

class EndMenu : public Menu {
    private:
        // Variables
        sf::Text* _endText;
        sf::Text* _scoreText;

        // Private Functions
        void initVariables();
        void initBackground();
        void initFont();
        void initText();

    public:
        // Constructor and Destructor
        EndMenu();
        virtual ~EndMenu();

        // Functions
        void update();
        void render(sf::RenderTarget& target);
};