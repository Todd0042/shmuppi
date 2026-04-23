#include "state_main_menu.hpp"
#include "state_level_select.hpp"
#include "game.hpp"
#include "raylib.h"
#include <iostream>

void StateMainMenu::handleInput(Game& game) {
    if (IsKeyPressed(KEY_ENTER)) {
        std::cout << "[INFO] Enter pressed: going to level select\n";
        game.pushState(std::make_unique<StateLevelSelect>());
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        std::cout << "[INFO] Escape pressed: quitting from main menu\n";
        game.requestQuit();
    }
}

void StateMainMenu::update(Game&, float) {
    // animations, etc.
}

void StateMainMenu::render(Game&) {
    DrawText("SHMUP CORE", 400, 200, 40, RAYWHITE);
    DrawText("Press ENTER to start", 420, 260, 20, GRAY);
    DrawText("Press ESC to quit",   420, 290, 20, GRAY);
}
