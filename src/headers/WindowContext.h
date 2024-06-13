#include <SFML/Graphics.hpp>

class WindowContext {
    private:
        static sf::RenderWindow* _window;
        static sf::View* _view;

    public:
        static void setWindow(sf::RenderWindow* window);
        static sf::RenderWindow* getWindow();
        static void setView(sf::View* view);
        static sf::View* getView();

        static sf::Vector2f getMousePosition();
};