#include "state_play.hpp"
#include "state_pause.hpp"
#include "game.hpp"
#include "raylib.h"
#include <iostream>
#include <algorithm>


StatePlay::StatePlay(int level_, int lives_)
    : level(level_), lives(lives_), player(200, 360)
{
    enemies.reserve(2000);   // space for enemies
    bullets.reserve(2000);   // space for bullets (we'll add bullets next)
}


void StatePlay::handleInput(Game& game) {
    if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_ESCAPE)) {
        std::cout << "[INFO] Pausing game\n";
        game.pushState(std::make_unique<StatePause>());
    }

    player.handleInput();

    // --- Player firing ---
    if (IsKeyDown(KEY_SPACE) && fireCooldown <= 0.0f) {
        Vector2 p = player.getPos();
        bullets.emplace_back(p.x + 20, p.y);  // spawn bullet slightly in front of player
        fireCooldown = 0.15f;                 // fire rate (seconds)
    }

}

void StatePlay::update(Game&, float dt) {
    enemySpawnTimer += dt;

    if (enemySpawnTimer > 0.6f) {
        enemySpawnTimer = 0.0f;

        float y = GetRandomValue(40, GetScreenHeight() - 40);

        // spawn a straight enemy just off the right side of the screen
        enemies.emplace_back(GetScreenWidth() + 40, y, EnemyType::Straight);
    }

    // update enemies
    for (auto& e : enemies) {
        e.update(dt);
    }

    // remove offscreen enemies
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
                    [](const Enemy& e){ return e.isOffscreen() || e.markForRemoval; }),
        enemies.end()
    );


    // --- bullet system ---
    fireCooldown -= dt;

    for (auto& b : bullets) {
        b.update(dt);
    }

    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
                    [](const Bullet& b){ return b.isOffscreen() || b.markForRemoval; }),
        bullets.end()
    );


    // --- Bullet → Enemy collisions ---
    for (auto& e : enemies) {
        Rectangle eh = e.hitbox();

        for (auto& b : bullets) {
            if (CheckCollisionRecs(eh, b.hitbox())) {
                e.markForRemoval = true;
                b.markForRemoval = true;
            }
        }
    }

    // --- Enemy → Player collisions ---
    for (auto& e : enemies) {
        if (CheckCollisionCircleRec(player.getPos(), player.getHitboxRadius(), e.hitbox())) {
            std::cout << "[HIT] Player took damage\n";
            // TODO: reduce lives, invincibility frames, etc.
        }
    }


    // update player
    player.update(dt);
}


void StatePlay::render(Game&) {
    ClearBackground(DARKBLUE);

    DrawText(TextFormat("Level %d", level), 20, 20, 20, RAYWHITE);
    DrawText(TextFormat("Lives %d", lives), 20, 50, 20, RAYWHITE);

    player.render();
    for (auto& e : enemies) {
        e.render();
    }
    for (auto& b : bullets) {
        b.render();
    }


}
