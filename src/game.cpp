#include "game.hpp"
#include "states/state.hpp"
#include "raylib.h"
#include <iostream>

Game::Game(const GameConfig& cfg) : config(cfg) {
    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_MAXIMIZED);
    InitWindow(config.width, config.height, config.title.c_str());


    SetTargetFPS(60);
}

Game::~Game() {
    CloseWindow();
}

void Game::run() {
    float lastTime = GetTime();

    while (!WindowShouldClose() && !shouldQuit) {
        float now = GetTime();
        float dt  = now - lastTime;
        lastTime  = now;

        if (auto* state = currentState()) {
            state->handleInput(*this);
            state->update(*this, dt);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (auto* state = currentState()) {
            state->render(*this);
        }

#ifdef SHMUP_DEBUG_WINDOW
        if (config.debug_window) {
            DrawText("DEBUG MODE", 10, 10, 20, RED);
        }
#endif

        EndDrawing();
    }
}

void Game::pushState(std::unique_ptr<GameState> state) {
    if (state) {
        state->onEnter(*this);
        states.emplace_back(std::move(state));
    }
}

void Game::popState() {
    if (!states.empty()) {
        states.back()->onExit(*this);
        states.pop_back();
    }
}

GameState* Game::currentState() {
    if (states.empty()) return nullptr;
    return states.back().get();
}
