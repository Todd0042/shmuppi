#include "player.hpp"
#include <cmath>
#include <algorithm>

Player::Player(float x, float y) {
    pos = {x, y};
    vel = {0, 0};

    sprite = LoadTexture("../assets/player/player_ship.png");
    TraceLog(LOG_INFO, "SPRITE SIZE: %d x %d", sprite.width, sprite.height);
}

Player::~Player() {
    UnloadTexture(sprite);
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

    // Invincibility countdown
    if (invulnTime > 0.0f) {
        invulnTime -= dt;
        if (invulnTime < 0.0f) invulnTime = 0.0f;
    }
}

void Player::render() const {
    // Flash during invulnerability
    bool flash = isInvulnerable() && (fmod(GetTime() * 20.0f, 2.0f) < 1.0f);
    Color tint = flash ? Color{255, 255, 255, 80} : WHITE;

    // --- Draw ship sprite ---
    float w = sprite.width * spriteScale;
    float h = sprite.height * spriteScale;

    Rectangle src{0, 0, (float)sprite.width, (float)sprite.height};
    Rectangle dst{pos.x - w * 0.5f, pos.y - h * 0.5f, w, h};

    DrawTexturePro(sprite, src, dst, {0, 0}, 0.0f, tint);

    // --- Power core glow ---
    float t = GetTime();
    float pulse = 1.0f + 0.25f * sinf(t * 6.0f);

    DrawCircleV(pos, hitboxRadius * 1.2f * pulse, Color{0, 150, 255, 40});
    DrawCircleV(pos, hitboxRadius * 1.0f * pulse, Color{0, 150, 255, 90});
    DrawCircleV(pos, hitboxRadius * 0.6f, Color{0, 180, 255, 255});
}

Rectangle Player::hitbox() const {
    return { pos.x - hitboxRadius, pos.y - hitboxRadius,
             hitboxRadius * 2, hitboxRadius * 2 };
}

void Player::takeDamage(int amount) {
    if (isInvulnerable()) return;

    health -= amount;
    if (health < 0) health = 0;

    // Start invincibility frames
    invulnTime = 1.2f;
}
