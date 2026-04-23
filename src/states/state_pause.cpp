#include "state_pause.hpp"
#include "game.hpp"
#include "raylib.h"
#include <iostream>

void StatePause::handleInput(Game& game) {
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_LEFT)) {
        selection = 0;
    }
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_RIGHT)) {
        selection = 1;
    }

    if (IsKeyPressed(KEY_ENTER)) {
        if (selection == 0) {
            std::cout << "[INFO] Continue from pause\n";
            game.popState(); // back to play
        } else {
            std::cout << "[INFO] Exit to main menu from pause\n";
            // pop pause + play
            game.popState();
            game.popState();
        }
    }
}

void StatePause::update(Game&, float) {}

void StatePause::render(Game&) {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5f));
    DrawText("PAUSED", 540, 250, 40, RAYWHITE);

    Color contColor = (selection == 0) ? YELLOW : GRAY;
    Color exitColor = (selection == 1) ? YELLOW : GRAY;

    DrawText("CONTINUE", 560, 320, 20, contColor);
    DrawText("EXIT TO MENU", 540, 350, 20, exitColor);
}
