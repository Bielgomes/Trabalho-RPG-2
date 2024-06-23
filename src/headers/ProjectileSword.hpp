#include "Projectile.hpp"

// Constructor
class ProjectileSword : public Projectile {
    public:
        // Constructor and Destructor
        ProjectileSword(sf::Vector2f direction, sf::Vector2f position, float rotation, int maxDistance, float size);
        virtual ~ProjectileSword() = default;
};