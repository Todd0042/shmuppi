#pragma once
#include "raylib.h"

enum class EnemyType {
    Straight,
    Sway,
    Turret,
    Mine,
    Seeker,
    Sniper
};

class Enemy {
public:
    Enemy(Texture2D sharedTexture, float x, float y, EnemyType type);

    void update(float dt);
    void render() const;

    Rectangle hitbox() const;
    bool isOffscreen() const;

    // Shooting helpers
    bool wantsToShoot() const { return shootTimer <= 0.01f; }
    Vector2 getGunPos() const;

    bool markForRemoval = false;

private:
    Vector2 pos;
    Vector2 vel;

    EnemyType type;

    float swayTimer = 0.0f;
    float shootTimer = 0.0f;

    // Shared texture — DO NOT unload in destructor
    Texture2D sprite;

    float spriteScale = 0.14f;
};
