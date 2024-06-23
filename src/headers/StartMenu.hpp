#pragma once

#include <vector>

#include "Menu.hpp"

class StartMenu : public Menu {
    private:
        // Variables
        sf::Texture* _texture;
        sf::Sprite* _sprite;

        std::string _name;

        // Name
        sf::Text* _nameText;

        int _classIndex;

        std::vector<sf::RectangleShape*> _classRectangles;

        // Private Functions
        void initVariables();
        void initBackground();
        void initFont();
        void initText();

    public:
        // Constructor and Destructor
        StartMenu();
        virtual ~StartMenu();

        // Accessors
        const int getClassIndex() const;
        const std::string getName() const;

        // Functions
        void pollEvent(sf::Event::TextEvent* textEvent);
        void update();

        void render(sf::RenderTarget& target);
};