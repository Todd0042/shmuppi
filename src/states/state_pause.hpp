#pragma once
#include "state.hpp"

class StatePause : public GameState {
public:
    void handleInput(Game& game) override;
    void update(Game& game, float dt) override;
    void render(Game& game) override;

private:
    int selection = 0; // 0 = continue, 1 = exit
};
