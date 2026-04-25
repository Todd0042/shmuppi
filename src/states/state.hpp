#pragma once
class Game;

class GameState {
public:
    virtual ~GameState() = default;

    virtual void onEnter(Game&) {}
    virtual void onExit(Game&) {}

    virtual void handleInput(Game& game) = 0;
    virtual void update(Game& game, float dt) = 0;
    virtual void render(Game& game) = 0;
};
