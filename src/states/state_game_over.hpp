#pragma once
#include "state.hpp"

class StateGameOver : public GameState {
public:
    void onEnter(Game& game) override {}
    void onExit(Game& game) override {}

    void handleInput(Game& game) override;
    void update(Game& game, float dt) override;
    void render(Game& game) override;
};
