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
    Enemy(float x, float y, EnemyType type);

    void update(float dt);
    void render() const;

    Rectangle hitbox() const;

    bool isOffscreen() const;
    bool markForRemoval = false;


private:
    Vector2 pos;
    Vector2 vel;
    float size = 24.0f;   // square hitbox
    EnemyType type;

    float swayTimer = 0.0f;
};
