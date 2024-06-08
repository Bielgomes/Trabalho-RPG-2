#include "SFML/Graphics.hpp"

class Game
{
    private:
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event event;

    public:
        // Accessors
        bool isRunning();

        // Constructor and Destructor
        Game();
        virtual ~Game();

        void pollEvents();
        void update();

        void render();
};