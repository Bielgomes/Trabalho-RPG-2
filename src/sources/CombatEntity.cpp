#include "../headers/CombatEntity.hpp"
#include "../headers/Character.hpp"

int CombatEntity::getDamage() {
    return _dmg;
}

int CombatEntity::getHp() {
    return _hp;
}

void CombatEntity::updatePhysics() {
    _velocity *= _velocityDesaceleration;

    if (std::abs(_velocity.x) < 0.1f)
        _velocity.x = 0.f;
    if (std::abs(_velocity.y) < 0.1f)
        _velocity.y = 0.f;
}