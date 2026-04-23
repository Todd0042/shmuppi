#include "game.hpp"
#include "states/state_main_menu.hpp"
#include <iostream>
#include <string_view>

int main(int argc, char** argv) {
    GameConfig cfg;

    // Basic CLI parsing
    for (int i = 1; i < argc; ++i) {
        std::string_view arg{argv[i]};
        if (arg == "--debug") {
            cfg.debug_window = true;
            std::cout << "[DEBUG] Debug window enabled via --debug\n";
        } else if (arg == "--no-console") {
            cfg.debug_console = false;
        }
    }

    if (cfg.debug_console) {
        std::cout << "[INFO] Starting shmup-core\n";
    }

    Game game{cfg};
    game.pushState(std::make_unique<StateMainMenu>());
    game.run();
    return 0;
}
