#pragma once

#include "Collision.h"
#include "Entity.h"

class CombatEntity : public Entity, public Collision {
    protected:
        // Variables
        int _hp;
        int _dmg;

    public:
        virtual int getDamage() = 0;
        virtual void takeDamage(int damage) = 0;
        virtual int getHp() = 0;
};