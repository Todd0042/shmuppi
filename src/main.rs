mod components;
mod game;
mod state;

use macroquad::prelude::*;
use game::*;
use state::GameState;

#[macroquad::main("shmuppi-rs")]
async fn main() {
    let mut world = World::new().await;

    loop {
        let dt = get_frame_time();

        match world.state {
            GameState::MainMenu => {
                update_main_menu(&mut world);
                render_main_menu();
            }
            GameState::LevelSelect => {
                update_level_select(&mut world);
                render_level_select(&world);
            }
            GameState::Playing => {
                update_play(&mut world, dt);
                render_play(&world);
            }
            GameState::Paused => {
                update_pause(&mut world);
                render_play(&world);
                render_pause();
            }
            GameState::GameOver => {
                update_game_over(&mut world);
                render_game_over();
            }
        }

        next_frame().await;
    }
}
