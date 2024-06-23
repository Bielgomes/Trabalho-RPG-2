#include <SFML/Graphics.hpp>

#include "OverlayMenu.hpp"

class InventoryMenu : public OverlayMenu {
    private:
        // Variables
        sf::Text* _characterName;
        sf::Text* _characterLevel;

        // Private Functions
        void initVariables();
        void initBackground();
        void initFont();
        void initText();

    public:
        // Constructor and Destructor
        InventoryMenu();
        virtual ~InventoryMenu();

        // Functions
        void update();
        void render(sf::RenderTarget& target);
};