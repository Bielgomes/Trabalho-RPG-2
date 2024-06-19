#include <SFML/Graphics.hpp>

class Inventory {
    private:
        // Variables
        sf::RectangleShape _overlay;
        sf::RectangleShape _background;

        bool _isOpen;

    public:
        // Constructor and Destructor
        Inventory();
        virtual ~Inventory();

        // Functions
        bool isOpen() const;
        void setIsOpen();

        void update();
        void render(sf::RenderTarget& target);
};