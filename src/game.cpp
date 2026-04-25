#include "game.hpp"
#include "states/state.hpp"
#include "raylib.h"
#include <iostream>

Game::Game(const GameConfig& cfg) : config(cfg) {
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

void Game::changeState(std::unique_ptr<GameState> state) {
    if (!states.empty()) {
        states.back()->onExit(*this);
        states.pop_back();
    }

    if (state) {
        state->onEnter(*this);
        states.emplace_back(std::move(state));
    }
}

GameState* Game::currentState() {
    if (states.empty()) return nullptr;
    return states.back().get();
}
