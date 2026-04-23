#pragma once
#include "state.hpp"

class StateLevelSelect : public GameState {
public:
    void handleInput(Game& game) override;
    void update(Game& game, float dt) override;
    void render(Game& game) override;

private:
    int selectedLives = 3;
    int selectedLevel = 1;
};
