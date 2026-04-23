#include "state_level_select.hpp"
#include "state_play.hpp"
#include "game.hpp"
#include "raylib.h"
#include <iostream>

void StateLevelSelect::handleInput(Game& game) {
    if (IsKeyPressed(KEY_UP))   selectedLives++;
    if (IsKeyPressed(KEY_DOWN)) selectedLives = std::max(1, selectedLives - 1);

    if (IsKeyPressed(KEY_LEFT))  selectedLevel = std::max(1, selectedLevel - 1);
    if (IsKeyPressed(KEY_RIGHT)) selectedLevel++;

    if (IsKeyPressed(KEY_ENTER)) {
        std::cout << "[INFO] Starting level " << selectedLevel
                  << " with lives " << selectedLives << "\n";
        game.pushState(std::make_unique<StatePlay>(selectedLevel, selectedLives));
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
        game.popState(); // back to main menu
    }
}

void StateLevelSelect::update(Game&, float) {}

void StateLevelSelect::render(Game&) {
    DrawText("LEVEL / LIVES SELECT", 360, 150, 30, RAYWHITE);

    DrawText(TextFormat("Lives: %d (UP/DOWN)", selectedLives), 380, 220, 20, GRAY);
    DrawText(TextFormat("Level: %d (LEFT/RIGHT)", selectedLevel), 380, 250, 20, GRAY);
    DrawText("ENTER to start, ESC to back", 380, 290, 20, GRAY);
}
