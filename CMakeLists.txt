cmake_minimum_required(VERSION 3.16)
project(shmuppi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(SHMUPPI_DEBUG_WINDOW "Enable debug overlay/window" ON)

find_package(raylib REQUIRED)

add_executable(shmuppi
    src/main.cpp
    src/game.cpp
    src/entities/player.cpp 
    src/entities/enemy.cpp  
    src/entities/bullet.cpp
    src/states/state_main_menu.cpp
    src/states/state_level_select.cpp
    src/states/state_play.cpp
    src/states/state_pause.cpp
)

target_include_directories(shmuppi PRIVATE src)

target_link_libraries(shmuppi PRIVATE raylib)

if (SHMUPPI_DEBUG_WINDOW)
    target_compile_definitions(shmuppi PRIVATE SHMUPPI_DEBUG_WINDOW=1)
endif()
