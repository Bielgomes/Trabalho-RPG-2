#include "Entity.hpp"

class Projectile : public Entity {
    protected:
        // Variables
        sf::Vector2f _direction;
        float _maxDistance;
        float _distanceTravelled;
        float _speed;
        int _bleeding;

        std::string _textureName;
        std::string _texturePath;

        int _dmg;

        // Private Functions
        void initVariables();
        void initTexture();
        void initSprite();

    public:
        // Constructor and Destructor
        virtual ~Projectile();

        // Accessors
        int getDamage() const;
        int getBleeding() const;

        // Functions
        void update();
        
        void listFree();
};