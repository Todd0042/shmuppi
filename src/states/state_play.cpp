#include "state_play.hpp"
#include "state_pause.hpp"
#include "game.hpp"
#include "raylib.h"
#include <iostream>
#include <algorithm>
#include "state_game_over.hpp"


StatePlay::StatePlay(int level_, int lives_)
    : level(level_), lives(lives_), player(200, 360)
{
    enemyTexture = LoadTexture("../assets/enemies/red_fighter.png");

    enemies.reserve(2000);
    bullets.reserve(2000);
    enemyBullets.reserve(2000);
}

StatePlay::~StatePlay() {
    UnloadTexture(enemyTexture);
}

void StatePlay::handleInput(Game& game) {
    if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_ESCAPE)) {
        game.pushState(std::make_unique<StatePause>());
    }

    player.handleInput();

    if (IsKeyDown(KEY_SPACE) && fireCooldown <= 0.0f) {
        Vector2 p = player.getPos();
        bullets.emplace_back(p.x + 20, p.y);
        fireCooldown = 0.15f;
    }
}

void StatePlay::update(Game& game, float dt) {
    enemySpawnTimer += dt;

    if (enemySpawnTimer > 0.6f) {
        enemySpawnTimer = 0.0f;

        float y = GetRandomValue(40, GetScreenHeight() - 40);
        float spawnX = GetScreenWidth() + GetRandomValue(180, 260);

        enemies.emplace_back(enemyTexture, spawnX, y, EnemyType::Straight);
    }

    for (auto& e : enemies) e.update(dt);

    for (auto& e : enemies) {
        if (e.wantsToShoot()) {
            Vector2 gp = e.getGunPos();
            enemyBullets.emplace_back(gp.x, gp.y);
        }
    }

    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const Enemy& e){ return e.isOffscreen() || e.markForRemoval; }),
        enemies.end()
    );

    fireCooldown -= dt;

    for (auto& b : bullets) b.update(dt);
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
            [](const Bullet& b){ return b.isOffscreen() || b.markForRemoval; }),
        bullets.end()
    );

    for (auto& eb : enemyBullets) eb.update(dt);
    enemyBullets.erase(
        std::remove_if(enemyBullets.begin(), enemyBullets.end(),
            [](const EnemyBullet& eb){ return eb.isOffscreen() || eb.markForRemoval; }),
        enemyBullets.end()
    );

    for (auto& e : enemies) {
        Rectangle eh = e.hitbox();
        for (auto& b : bullets) {
            if (CheckCollisionRecs(eh, b.hitbox())) {
                e.markForRemoval = true;
                b.markForRemoval = true;
            }
        }
    }

    // Enemy bullet → Player
    for (auto& eb : enemyBullets) {
        if (CheckCollisionCircleRec(player.getPos(), player.getHitboxRadius(), eb.hitbox())) {
            eb.markForRemoval = true;

            if (!player.isInvulnerable()) {
                player.takeDamage(1);
                std::cout << "[HP] Player HP: " << player.health << "\n";
            }
        }
    }

    // Enemy → Player
    for (auto& e : enemies) {
        if (CheckCollisionCircleRec(player.getPos(), player.getHitboxRadius(), e.hitbox())) {
            if (!player.isInvulnerable()) {
                player.takeDamage(1);
                std::cout << "[HP] Player HP: " << player.health << "\n";
            }
        }
    }

    // --- Player death + respawn ---
    if (player.health <= 0) {
        lives--;

        if (lives <= 0) {
            std::cout << "[GAME OVER]\n";
            game.changeState(std::make_unique<StateGameOver>());
            return; // stop updating this state
        } else {
            // Respawn player
            player.health = player.maxHealth;
            player.invulnTime = 2.0f;
            player.setPos({200, 360});
        }
    }


    player.update(dt);
}

void StatePlay::render(Game&) {
    ClearBackground(DARKBLUE);

    DrawText(TextFormat("Level %d", level), 20, 20, 20, RAYWHITE);
    DrawText(TextFormat("Lives %d", lives), 20, 50, 20, RAYWHITE);

    // --- Player Health Bar ---
    float barWidth = 200.0f;
    float barHeight = 20.0f;

    float healthPercent = (float)player.health / (float)player.maxHealth;
    float filledWidth = barWidth * healthPercent;

    DrawRectangle(20, 80, barWidth, barHeight, DARKGRAY);
    DrawRectangle(20, 80, filledWidth, barHeight, RED);
    DrawRectangleLines(20, 80, barWidth, barHeight, BLACK);

    DrawText(TextFormat("HP: %d/%d", player.health, player.maxHealth),
            25, 82, 16, WHITE);

    player.render();

    for (auto& e : enemies) e.render();
    for (auto& b : bullets) b.render();
    for (auto& eb : enemyBullets) eb.render();
}
