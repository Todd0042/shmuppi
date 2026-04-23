#pragma once
#include "state.hpp"
#include "../entities/player.hpp"

class StatePlay : public GameState {
public:
    StatePlay(int level, int lives);

    void handleInput(Game& game) override;
    void update(Game& game, float dt) override;
    void render(Game& game) override;

private:
    int level;
    int lives;

    Player player;
};
