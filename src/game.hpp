#pragma once
#include <memory>
#include <string>
#include <vector>

struct GameConfig {
    bool debug_console = true;
    bool debug_window  = false;
    int  width         = 1280;
    int  height        = 720;
    std::string title  = "shmuppi";
};

class GameState;

class Game {
public:
    explicit Game(const GameConfig& cfg);
    ~Game();

    void run();

    void requestQuit() { shouldQuit = true; }

    void pushState(std::unique_ptr<GameState> state);
    void popState();
    void changeState(std::unique_ptr<GameState> state);

    GameState* currentState();

    bool isDebugWindowEnabled() const { return config.debug_window; }

private:
    GameConfig config;
    bool shouldQuit = false;
    std::vector<std::unique_ptr<GameState>> states;
};
