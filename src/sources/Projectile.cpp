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

    _direction = sf::Vector2f(0.f, 0.f);
}

void Projectile::initTexture() {
    sf::Texture* projectileTexture = Context::getTextureContext()->getTexture("PROJECTILE");
    if (projectileTexture == nullptr) {
        projectileTexture = new sf::Texture();
        if (!projectileTexture->loadFromFile("src/resources/textures/knightSwordSprite.png")) {
            std::cout << "ERROR::GAME::INITTEXTURES::Could not load projectile texture file." << std::endl;
        }
        Context::getTextureContext()->addTexture("PROJECTILE", projectileTexture);
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
Projectile::Projectile(sf::Vector2f direction, sf::Vector2f position, float rotation) {
    initVariables();
    initTexture();
    initSprite();

    _direction = direction * _speed;
    _sprite->setPosition(position);
    _sprite->setRotation(rotation + 90);
}

Projectile::~Projectile() {
    delete _sprite;
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