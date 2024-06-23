#include "Projectile.hpp"

// Constructor
class ProjectileArrow : public Projectile {
    public:
        // Constructor and Destructor
        ProjectileArrow(sf::Vector2f direction, sf::Vector2f position, float rotation, int maxDistance);
        virtual ~ProjectileArrow() = default;
};