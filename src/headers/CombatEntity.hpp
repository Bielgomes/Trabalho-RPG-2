#pragma once

#include "Collision.hpp"
#include "Entity.hpp"

class CombatEntity : public Entity, public Collision {
    protected:
        // Variables
        int _hp;
        int _dmg;
        int _xp;
        
        sf::Vector2f _velocity;
        float _velocityMax;
        float _velocityAceleration;
        float _velocityDesaceleration;

        sf::Clock _invencibilityTimer;

    public:
        int getDamage();
        virtual void takeDamage(int damage, sf::Vector2f direction) = 0;
        int getHp();

        void updatePhysics();
        virtual void updateMovement() = 0;
};