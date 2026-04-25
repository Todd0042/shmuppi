#include "enemy_bullet.hpp"
#include "raylib.h"

EnemyBullet::EnemyBullet(float x, float y)
    : pos{ x, y }
{
}

void EnemyBullet::update(float dt) {
    // Enemy bullets move LEFT across the screen
    pos.x -= speed * dt;
}

void EnemyBullet::render() const {
    // Simple red circle bullet
    DrawCircleV(pos, radius, RED);
}

Rectangle EnemyBullet::hitbox() const {
    return {
        pos.x - radius,
        pos.y - radius,
        radius * 2.0f,
        radius * 2.0f
    };
}

bool EnemyBullet::isOffscreen() const {
    return pos.x + radius < 0;
}
