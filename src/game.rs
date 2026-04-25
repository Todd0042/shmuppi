use macroquad::prelude::*;

use crate::components::{Bullet, Enemy, EnemyBullet, Player};
use crate::state::GameState;

pub struct World {
    pub state: GameState,
    pub level: i32,
    pub lives: i32,
    pub selected_lives: i32,

    pub player: Player,
    pub bullets: Vec<Bullet>,
    pub enemies: Vec<Enemy>,
    pub enemy_bullets: Vec<EnemyBullet>,

    pub enemy_spawn_timer: f32,
    pub fire_cooldown: f32,

    pub tex_player: Texture2D,
    pub tex_enemy: Texture2D,
}

impl World {
    pub async fn new() -> Self {
        let tex_player = load_texture("assets/player.png").await.unwrap_or_else(|_| {
            warn!("Failed to load player texture, using white rect");
            Texture2D::from_image(&Image::gen_image_color(32, 32, WHITE))
        });

        let tex_enemy =
            load_texture("assets/enemies/red_fighter.png").await.unwrap_or_else(|_| {
                warn!("Failed to load enemy texture, using red rect");
                Texture2D::from_image(&Image::gen_image_color(32, 32, RED))
            });

        Self {
            state: GameState::MainMenu,
            level: 1,
            lives: 3,
            selected_lives: 3,
            player: Player::new(),
            bullets: Vec::with_capacity(2000),
            enemies: Vec::with_capacity(2000),
            enemy_bullets: Vec::with_capacity(2000),
            enemy_spawn_timer: 0.0,
            fire_cooldown: 0.0,
            tex_player,
            tex_enemy,
        }
    }

    pub fn reset_for_level(&mut self, level: i32, lives: i32) {
        self.level = level;
        self.lives = lives;
        self.player = Player::new();
        self.bullets.clear();
        self.enemies.clear();
        self.enemy_bullets.clear();
        self.enemy_spawn_timer = 0.0;
        self.fire_cooldown = 0.0;
    }
}

// ---------- main menu ----------

pub fn update_main_menu(world: &mut World) {
    if is_key_pressed(KeyCode::Enter) {
        world.state = GameState::LevelSelect;
    }
}

pub fn render_main_menu() {
    clear_background(BLACK);
    draw_text("SHMUPPI (Rust)", 200.0, 200.0, 60.0, WHITE);
    draw_text("Press ENTER to start", 200.0, 280.0, 30.0, GRAY);
}

// ---------- level select (with lives selection) ----------

pub fn update_level_select(world: &mut World) {
    // Level selection: 1, 2, 3
    if is_key_pressed(KeyCode::Key1) {
        world.level = 1;
    }
    if is_key_pressed(KeyCode::Key2) {
        world.level = 2;
    }
    if is_key_pressed(KeyCode::Key3) {
        world.level = 3;
    }

    // Lives selection: 3, 5, 7
    if is_key_pressed(KeyCode::Key3) {
        world.selected_lives = 3;
    }
    if is_key_pressed(KeyCode::Key5) {
        world.selected_lives = 5;
    }
    if is_key_pressed(KeyCode::Key7) {
        world.selected_lives = 7;
    }

    // Start game
    if is_key_pressed(KeyCode::Enter) {
        world.reset_for_level(world.level, world.selected_lives);
        world.state = GameState::Playing;
    }
}

pub fn render_level_select(world: &World) {
    clear_background(BLACK);
    draw_text("Select Level", 200.0, 160.0, 40.0, WHITE);
    draw_text("1, 2, or 3", 200.0, 210.0, 30.0, GRAY);

    draw_text(
        &format!("Current level: {}", world.level),
        200.0,
        250.0,
        24.0,
        WHITE,
    );

    draw_text("Select Lives (3, 5, 7)", 200.0, 300.0, 30.0, GRAY);
    draw_text(
        &format!("Current lives: {}", world.selected_lives),
        200.0,
        340.0,
        24.0,
        WHITE,
    );

    draw_text("Press ENTER to start", 200.0, 400.0, 30.0, WHITE);
}

// ---------- playing ----------

pub fn update_play(world: &mut World, dt: f32) {
    // Pause
    if is_key_pressed(KeyCode::Escape) || is_key_pressed(KeyCode::P) {
        world.state = GameState::Paused;
        return;
    }

    // Player movement
    {
        let p = &mut world.player;
        if is_key_down(KeyCode::Left) {
            p.pos.x -= p.speed * dt;
        }
        if is_key_down(KeyCode::Right) {
            p.pos.x += p.speed * dt;
        }
        if is_key_down(KeyCode::Up) {
            p.pos.y -= p.speed * dt;
        }
        if is_key_down(KeyCode::Down) {
            p.pos.y += p.speed * dt;
        }

        if p.invuln_time > 0.0 {
            p.invuln_time -= dt;
        }
    }

    // Shooting
    world.fire_cooldown -= dt;
    if is_key_down(KeyCode::Space) && world.fire_cooldown <= 0.0 {
        let p = &world.player;
        world
            .bullets
            .push(Bullet::new(p.pos.x + 20.0, p.pos.y));
        world.fire_cooldown = 0.15;
    }

    // Enemy spawn (scale with level)
    world.enemy_spawn_timer += dt;
    let spawn_interval = match world.level {
        1 => 0.6,
        2 => 0.45,
        3 => 0.3,
        _ => 0.6,
    };

    if world.enemy_spawn_timer > spawn_interval {
        world.enemy_spawn_timer = 0.0;
        let y = rand::gen_range(40.0, screen_height() - 40.0);
        world.enemies.push(Enemy::new_straight(y));
    }

    // Update enemies
    for e in &mut world.enemies {
        e.pos.x -= e.speed * dt;
    }

    // Enemy shooting (probability-based, slower)
    let shoot_chance = match world.level {
        1 => 0.004,
        2 => 0.006,
        3 => 0.008,
        _ => 0.004,
    };

    for e in &world.enemies {
        if rand::gen_range(0.0, 1.0) < shoot_chance {
            world
                .enemy_bullets
                .push(EnemyBullet::new(e.pos.x - 12.0, e.pos.y));
        }
    }

    // Cleanup enemies
    world
        .enemies
        .retain(|e| e.pos.x > -100.0 && !e.dead);

    // Update bullets
    for b in &mut world.bullets {
        b.pos.x += b.speed * dt;
    }
    world
        .bullets
        .retain(|b| b.pos.x < screen_width() + 100.0 && !b.dead);

    // Update enemy bullets
    for eb in &mut world.enemy_bullets {
        eb.pos.x -= eb.speed * dt;
    }
    world
        .enemy_bullets
        .retain(|eb| eb.pos.x > -100.0 && !eb.dead);

    // Bullet → Enemy collisions
    for e in &mut world.enemies {
        let eh = e.hitbox();
        for b in &mut world.bullets {
            let bh = Rect::new(b.pos.x, b.pos.y, 10.0, 4.0);
            if eh.overlaps(&bh) {
                e.dead = true;
                b.dead = true;
            }
        }
    }

    // Enemy bullet → Player
    {
        let p = &mut world.player;
        for eb in &mut world.enemy_bullets {
            if p.pos.distance(eb.pos) < p.hitbox_radius() && !p.is_invulnerable() {
                eb.dead = true;
                p.health -= 1;
                println!("[HP] Player HP: {}", p.health);
            }
        }
    }

    // Enemy → Player
    {
        let p = &mut world.player;
        for e in &mut world.enemies {
            if p.pos.distance(e.pos) < p.hitbox_radius() + 16.0 && !p.is_invulnerable() {
                e.dead = true;
                p.health -= 1;
                println!("[HP] Player HP: {}", p.health);
            }
        }
    }

    // Player death + lives
    if world.player.health <= 0 {
        world.lives -= 1;

        if world.lives <= 0 {
            println!("[GAME OVER]");
            world.state = GameState::GameOver;
            return;
        } else {
            // Respawn
            world.player.health = world.player.max_health;
            world.player.invuln_time = 2.0;
            world.player.pos = vec2(200.0, 360.0);
        }
    }
}

pub fn render_play(world: &World) {
    clear_background(DARKBLUE);

    // HUD
    draw_text(
        &format!("Level {}", world.level),
        20.0,
        30.0,
        24.0,
        WHITE,
    );
    draw_text(
        &format!("Lives {}", world.lives),
        20.0,
        60.0,
        24.0,
        WHITE,
    );

    // HP bar
    let bar_width = 200.0;
    let bar_height = 20.0;
    let hp_percent = world.player.health as f32 / world.player.max_health as f32;
    let filled = bar_width * hp_percent;

    draw_rectangle(20.0, 80.0, bar_width, bar_height, DARKGRAY);
    draw_rectangle(20.0, 80.0, filled, bar_height, RED);
    draw_rectangle_lines(20.0, 80.0, bar_width, bar_height, 2.0, BLACK);

    draw_text(
        &format!("HP: {}/{}", world.player.health, world.player.max_health),
        25.0,
        96.0,
        16.0,
        WHITE,
    );

    // Player (blink during invuln)
    let blink = world.player.invuln_time > 0.0
        && ((get_time() * 10.0) as i32 % 2 == 0);

    if !blink {
        draw_texture(
            &world.tex_player,
            world.player.pos.x - 16.0,
            world.player.pos.y - 16.0,
            WHITE,
        );
    }

    // Enemies
    for e in &world.enemies {
        draw_texture(&world.tex_enemy, e.pos.x - 16.0, e.pos.y - 16.0, WHITE);
    }

    // Bullets
    for b in &world.bullets {
        draw_rectangle(b.pos.x, b.pos.y, 10.0, 4.0, YELLOW);
    }

    // Enemy bullets
    for eb in &world.enemy_bullets {
        draw_circle(eb.pos.x, eb.pos.y, 4.0, RED);
    }
}

// ---------- pause ----------

pub fn update_pause(world: &mut World) {
    if is_key_pressed(KeyCode::Escape) || is_key_pressed(KeyCode::P) {
        world.state = GameState::Playing;
    }
}

pub fn render_pause() {
    draw_text("PAUSED", 400.0, 200.0, 60.0, WHITE);
    draw_text("Press ESC or P to resume", 300.0, 280.0, 30.0, GRAY);
}

// ---------- game over ----------

pub fn update_game_over(world: &mut World) {
    if is_key_pressed(KeyCode::Enter) {
        // Back to main menu
        world.state = GameState::MainMenu;
    }
}

pub fn render_game_over() {
    clear_background(BLACK);
    draw_text("GAME OVER", 350.0, 250.0, 60.0, RED);
    draw_text("Press ENTER to return to menu", 250.0, 330.0, 30.0, WHITE);
}
