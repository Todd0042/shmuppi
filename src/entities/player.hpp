#pragma once
#include "raylib.h"

class Player {
public:
    Player(float x, float y);

    void handleInput();
    void update(float dt);
    void render() const;

    Rectangle hitbox() const;

private:
    Vector2 pos;
    Vector2 vel;

    float speed = 350.0f;
    float hitboxRadius = 6.0f; // tiny power-core style hitbox

    // future weapon state
    // int weaponMode = 0;
    // float fireCooldown = 0.0f;
};
