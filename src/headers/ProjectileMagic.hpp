#include "Projectile.hpp"

// Constructor
class ProjectileMagic : public Projectile {
    public:
        // Constructor and Destructor
        ProjectileMagic(sf::Vector2f direction, sf::Vector2f position, float rotation, int maxDistance, float size);
        virtual ~ProjectileMagic() = default;
};