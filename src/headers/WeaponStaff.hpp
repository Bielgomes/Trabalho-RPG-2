#pragma once

#include "Weapon.hpp"

class WeaponStaff : public Weapon {
    public:
        // Constructor and Destructor
        WeaponStaff(CombatEntity* entity);
        ~WeaponStaff() = default;
};