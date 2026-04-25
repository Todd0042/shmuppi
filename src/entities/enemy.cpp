#include "enemy.hpp"
#include "raylib.h"
#include <cmath>

Enemy::Enemy(Texture2D sharedTexture, float x, float y, EnemyType type)
    : sprite(sharedTexture), pos{ x, y }, type(type)
{
    vel = { -120.0f, 0.0f };
    spriteScale = 0.14f;
}

void Enemy::update(float dt) {
    // Movement
    pos.x += vel.x * dt;
    pos.y += vel.y * dt;

    // Swaying movement
    if (type == EnemyType::Sway) {
        swayTimer += dt * 3.0f;
        pos.y += std::sinf(swayTimer) * 40.0f * dt;
    }

    // Shooting timer
    shootTimer += dt;
    if (shootTimer > 1.2f) {
        shootTimer = 0.0f;
    }
}

void Enemy::render() const {
    float w = sprite.width * spriteScale;
    float h = sprite.height * spriteScale;

    // Your PNG already faces LEFT — draw normally
    Rectangle src{
        0.0f,
        0.0f,
        (float)sprite.width,
        (float)sprite.height
    };

    Rectangle dst{
        pos.x - w * 0.5f,
        pos.y - h * 0.5f,
        w,
        h
    };

    DrawTexturePro(sprite, src, dst, {0, 0}, 0.0f, WHITE);
}

Rectangle Enemy::hitbox() const {
    float w = sprite.width * spriteScale;
    float h = sprite.height * spriteScale;

    return {
        pos.x - w * 0.5f,
        pos.y - h * 0.5f,
        w,
        h
    };
}

bool Enemy::isOffscreen() const {
    float w = sprite.width * spriteScale;
    return pos.x + w < 0;
}

Vector2 Enemy::getGunPos() const {
    float w = sprite.width * spriteScale;
    return { pos.x - w * 0.5f, pos.y };
}
