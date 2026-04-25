#pragma once
#include "raylib.h"

class Player {
public:
    Player(float x, float y);
    ~Player();

    void handleInput();
    void update(float dt);
    void render() const;

    Vector2 getPos() const { return pos; }
    float getHitboxRadius() const { return hitboxRadius; }
    Rectangle hitbox() const;

    void setPos(Vector2 p) { pos = p; }

    // --- Health + Lives ---
    int health = 5;
    int maxHealth = 5;

    // --- Invincibility frames ---
    float invulnTime = 0.0f;
    bool isInvulnerable() const { return invulnTime > 0.0f; }

    void takeDamage(int amount);

private:
    Vector2 pos;
    Vector2 vel;

    float speed = 260.0f;
    float hitboxRadius = 20.0f;

    // Player sprite
    Texture2D sprite;
    float spriteScale = 0.22f;
};
