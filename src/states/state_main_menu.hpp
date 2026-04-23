#pragma once
#include "state.hpp"
#include "../entities/bullet.hpp"

class StateMainMenu : public GameState {
public:
    void handleInput(Game& game) override;
    void update(Game& game, float dt) override;
    void render(Game& game) override;
};
