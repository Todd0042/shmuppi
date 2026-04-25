#include "state_game_over.hpp"
#include "state_main_menu.hpp"
#include "game.hpp"
#include "raylib.h"
#include <iostream>

void StateGameOver::handleInput(Game& game) {
    if (IsKeyPressed(KEY_ENTER)) {
        game.changeState(std::make_unique<StateMainMenu>());
    }
}

void StateGameOver::update(Game&, float) {
    // No updates needed
}

void StateGameOver::render(Game&) {
    ClearBackground(BLACK);

    DrawText("GAME OVER", 400, 250, 60, RED);
    DrawText("Press ENTER to return to menu", 350, 350, 30, WHITE);
}
