#pragma once

#include "Weapon.hpp"

class WeaponSword : public Weapon {
    public:
        // Constructor and Destructor
        WeaponSword(CombatEntity* entity);
        ~WeaponSword() = default;
};