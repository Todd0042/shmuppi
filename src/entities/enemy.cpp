#include "enemy.hpp"
#include <cmath>

Enemy::Enemy(float x, float y, EnemyType t)
    : pos{x, y}, type(t)
{
    switch (type) {
        case EnemyType::Straight:
            vel = {-180.0f, 0.0f};
            break;

        case EnemyType::Sway:
            vel = {-140.0f, 0.0f};
            break;

        case EnemyType::Turret:
            vel = {-60.0f, 0.0f};
            break;

        case EnemyType::Mine:
            vel = {-80.0f, 0.0f};
            break;

        case EnemyType::Seeker:
            vel = {-120.0f, 0.0f};
            break;

        case EnemyType::Sniper:
            vel = {-100.0f, 0.0f};
            break;
    }
}

void Enemy::update(float dt) {
    if (type == EnemyType::Sway) {
        swayTimer += dt * 3.0f;
        pos.y += sinf(swayTimer) * 60.0f * dt;
    }

    pos.x += vel.x * dt;
    pos.y += vel.y * dt;
}

void Enemy::render() const {
    Rectangle r = hitbox();
    DrawRectangleRec(r, Color{255, 80, 80, 255});
    DrawRectangleLinesEx(r, 2, Color{120, 20, 20, 255});
}

Rectangle Enemy::hitbox() const {
    return { pos.x - size * 0.5f, pos.y - size * 0.5f, size, size };
}

bool Enemy::isOffscreen() const {
    return pos.x + size < 0;
}
