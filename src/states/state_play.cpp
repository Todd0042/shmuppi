#include "state_play.hpp"
#include "state_pause.hpp"
#include "game.hpp"
#include "raylib.h"
#include <iostream>

StatePlay::StatePlay(int level_, int lives_)
    : level(level_), lives(lives_), player(200, 360) {}

void StatePlay::handleInput(Game& game) {
    if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_ESCAPE)) {
        std::cout << "[INFO] Pausing game\n";
        game.pushState(std::make_unique<StatePause>());
    }

    player.handleInput();
}

void StatePlay::update(Game&, float dt) {
    player.update(dt);
}

void StatePlay::render(Game&) {
    ClearBackground(DARKBLUE);

    DrawText(TextFormat("Level %d", level), 20, 20, 20, RAYWHITE);
    DrawText(TextFormat("Lives %d", lives), 20, 50, 20, RAYWHITE);

    player.render();
}
