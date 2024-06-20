#include <SFML/Graphics.hpp>

#include "OverlayMenu.hpp"

class InventoryMenu : public OverlayMenu {
    private:
        // Private Functions
        void initVariables();
        void initBackground();

    public:
        // Constructor and Destructor
        InventoryMenu();
        virtual ~InventoryMenu();

        // Functions
        void update();
        void render(sf::RenderTarget& target);
};