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

    public:
        int getDamage();
        void takeDamage(int damage);
        int getHp();

        void updatePhysics();
        virtual void updateMovement() = 0;

        virtual void listFree() = 0;
};