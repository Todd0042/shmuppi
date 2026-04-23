#pragma once
#include "state.hpp"
#include "../entities/player.hpp"
#include "../entities/enemy.hpp"
#include <vector>
#include "../entities/bullet.hpp"


class StatePlay : public GameState {
public:
    StatePlay(int level, int lives);

    void handleInput(Game& game) override;
    void update(Game& game, float dt) override;
    void render(Game& game) override;

private:
    int level;
    int lives;

    Player player;

    std::vector<Enemy> enemies;
    float enemySpawnTimer = 0.0f;

    std::vector<Bullet> bullets;
    float fireCooldown = 0.0f;

};
