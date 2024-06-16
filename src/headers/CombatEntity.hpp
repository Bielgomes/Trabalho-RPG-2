#pragma once

#include "Collision.hpp"
#include "Entity.hpp"

class CombatEntity : public Entity, public Collision {
    protected:
        // Variables
        int _hp;
        int _dmg;
        float _speed;

    public:
        virtual int getDamage() = 0;
        virtual void takeDamage(int damage) = 0;
        virtual int getHp() = 0;

        virtual void listFree() = 0;
};