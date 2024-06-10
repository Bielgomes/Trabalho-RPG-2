#include <SFML/Graphics.hpp>

class Game {
    private:
        // Window
        sf::RenderWindow* _window;
        sf::Event _event;

        // Private Functions
        void initVariables();
        void initWindow();

    public:
        // Constructor and Destructor
        Game();
        virtual ~Game();

        void run();
        void pollEvents();
        void update();
        void render();
};