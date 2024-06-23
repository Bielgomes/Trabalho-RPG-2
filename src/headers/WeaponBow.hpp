#pragma once

#include "Weapon.hpp"

class WeaponBow : public Weapon {
    public:
        // Constructor and Destructor
        WeaponBow(CombatEntity* entity);
        ~WeaponBow() = default;

        // Functions
        void update();

        void listFree();
};