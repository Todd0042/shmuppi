#include "player.hpp"
#include <cmath>
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
    // --- Temporary ship body (wide rectangle) ---
    const float shipWidth  = 48.0f;
    const float shipHeight = 20.0f;

    Rectangle shipRect{
        pos.x - shipWidth * 0.5f,
        pos.y - shipHeight * 0.5f,
        shipWidth,
        shipHeight
    };

    DrawRectangleRounded(shipRect, 0.3f, 6, Color{200, 200, 200, 255});
    DrawRectangleRoundedLines(shipRect, 0.3f, 6, Color{80, 80, 80, 255});

    // --- Power core (actual hitbox) ---
    // --- Power core glow layers ---
    float t = GetTime();

    // Pulse between 1.0 and 1.25
    float pulse = 1.0f + 0.25f * sinf(t * 6.0f);

    // Outer halo
    DrawCircleV(pos, hitboxRadius * 4.0f * pulse,
                Color{0, 150, 255, 40});

    // Mid halo
    DrawCircleV(pos, hitboxRadius * 2.5f * pulse,
                Color{0, 150, 255, 90});

    // Inner bright core (actual hitbox)
    DrawCircleV(pos, hitboxRadius,
                Color{0, 180, 255, 255});

}




Rectangle Player::hitbox() const {
    return { pos.x - hitboxRadius, pos.y - hitboxRadius,
             hitboxRadius * 2, hitboxRadius * 2 };
}
