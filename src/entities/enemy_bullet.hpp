#pragma once
#include "raylib.h"

class EnemyBullet {
public:
    EnemyBullet(float x, float y);

    void update(float dt);
    void render() const;

    Rectangle hitbox() const;
    bool isOffscreen() const;

    bool markForRemoval = false;

private:
    Vector2 pos;
    float speed = 260.0f;
    float radius = 6.0f;
};
