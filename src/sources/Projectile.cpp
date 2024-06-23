#include "../headers/Context.hpp"
#include "../headers/Functions.hpp"
#include "../headers/Projectile.hpp"

// Private Functions
void Projectile::initVariables() {
    _texture = nullptr;
    _sprite = nullptr;

    _maxDistance = 60.f;
    _distanceTravelled = 0.f;
    _speed = 3.f;

    _dmg = 2;

    _direction = sf::Vector2f(0.f, 0.f);
}

void Projectile::initTexture() {
    sf::Texture* projectileTexture = Context::getTextureContext()->getTexture(_textureName);
    if (projectileTexture == nullptr) {
        projectileTexture = new sf::Texture();
        if (!projectileTexture->loadFromFile("src/resources/textures/" + _texturePath + ".png")) {
            std::cout << "ERROR::GAME::INITTEXTURES::Could not load projectile texture file." << std::endl;
        }
        Context::getTextureContext()->addTexture(_textureName, projectileTexture);
    }

    _texture = projectileTexture;
}

void Projectile::initSprite() {
    _sprite = new sf::Sprite(*_texture);
    _sprite->setOrigin(
        getPosition().x + getShape().width / 2,
        getShape().height
    );
}

// Constructor and Destructor
Projectile::~Projectile() {
    delete _sprite;
}

// Accessors
int Projectile::getDamage() const {
    return _dmg;
}

// Functions
void Projectile::update() {
    if (_distanceTravelled > _maxDistance)
        return listFree();

    _sprite->move(_direction);
    _distanceTravelled += Functions::vectorMagnitude(_direction);
}

void Projectile::listFree() {
    Context::getEntityContext()->removeFromGroup("PROJECTILE", this);
}