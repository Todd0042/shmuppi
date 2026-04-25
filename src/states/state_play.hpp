#pragma once
#include "state.hpp"
#include "../entities/player.hpp"
#include "../entities/enemy.hpp"
#include "../entities/bullet.hpp"
#include "../entities/enemy_bullet.hpp"
#include <vector>
#include "raylib.h"

class StatePlay : public GameState {
public:
    StatePlay(int level, int lives);
    ~StatePlay();   // unload shared textures

    void handleInput(Game& game) override;
    void update(Game& game, float dt) override;

    void render(Game& game) override;

private:
    int level;
    int lives;

    Player player;

    // Shared enemy texture (prevents garbage-frame rendering)
    Texture2D enemyTexture;

    // Enemies
    std::vector<Enemy> enemies;
    float enemySpawnTimer = 0.0f;

    // Player bullets
    std::vector<Bullet> bullets;
    float fireCooldown = 0.0f;

    // Enemy bullets
    std::vector<EnemyBullet> enemyBullets;
};
