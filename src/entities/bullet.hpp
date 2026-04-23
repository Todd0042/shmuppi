#pragma once
#include "raylib.h"

class Bullet {
public:
    Bullet(float x, float y);

    void update(float dt);
    void render() const;

    Rectangle hitbox() const;
    bool isOffscreen() const;
    bool markForRemoval = false;


private:
    Vector2 pos;
    float speed = 600.0f;
    float size = 6.0f;
};
