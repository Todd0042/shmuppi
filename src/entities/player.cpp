#include "player.hpp"
#include <algorithm>

Player::Player(float x, float y) {
    pos = {x, y};
    vel = {0, 0};
}

void Player::handleInput() {
    vel = {0, 0};

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    vel.y = -1;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  vel.y =  1;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  vel.x = -1;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) vel.x =  1;

    // normalize diagonal
    if (vel.x != 0 || vel.y != 0) {
        float mag = sqrtf(vel.x * vel.x + vel.y * vel.y);
        vel.x /= mag;
        vel.y /= mag;
    }
}

void Player::update(float dt) {
    pos.x += vel.x * speed * dt;
    pos.y += vel.y * speed * dt;

    // clamp to screen
    pos.x = std::clamp(pos.x, 0.0f, (float)GetScreenWidth());
    pos.y = std::clamp(pos.y, 0.0f, (float)GetScreenHeight());
}

void Player::render() const {
    // draw tiny core hitbox
    DrawCircleV(pos, hitboxRadius, YELLOW);

    // optional: draw a larger visible ship placeholder
    DrawTriangle(
        {pos.x, pos.y - 12},
        {pos.x - 10, pos.y + 12},
        {pos.x + 10, pos.y + 12},
        RAYWHITE
    );
}

Rectangle Player::hitbox() const {
    return { pos.x - hitboxRadius, pos.y - hitboxRadius,
             hitboxRadius * 2, hitboxRadius * 2 };
}
