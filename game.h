#include "SFML/Graphics.hpp"

class Game
{
    private:
        sf::VideoMode videoMode;
        sf::RenderWindow* window;

    public:
        // Accessors
        bool isRunning();

        // Constructor and Destructor
        Game();
        ~Game();

        void update();

        void render();
};