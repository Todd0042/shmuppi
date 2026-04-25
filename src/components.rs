use macroquad::prelude::*;

#[derive(Clone, Copy)]
pub enum EnemyType {
    Straight,
}

pub struct Player {
    pub pos: Vec2,
    pub speed: f32,
    pub health: i32,
    pub max_health: i32,
    pub invuln_time: f32,
}

impl Player {
    pub fn new() -> Self {
        Self {
            pos: vec2(200.0, 360.0),
            speed: 300.0,
            health: 3,
            max_health: 3,
            invuln_time: 0.0,
        }
    }

    pub fn hitbox_radius(&self) -> f32 {
        16.0
    }

    pub fn is_invulnerable(&self) -> bool {
        self.invuln_time > 0.0
    }
}

pub struct Bullet {
    pub pos: Vec2,
    pub speed: f32,
    pub dead: bool,
}

impl Bullet {
    pub fn new(x: f32, y: f32) -> Self {
        Self {
            pos: vec2(x, y),
            speed: 600.0,
            dead: false,
        }
    }
}

pub struct Enemy {
    pub pos: Vec2,
    pub speed: f32,
    pub enemy_type: EnemyType,
    pub dead: bool,
}

impl Enemy {
    pub fn new_straight(y: f32) -> Self {
        Self {
            pos: vec2(screen_width() + 200.0, y),
            speed: 200.0,
            enemy_type: EnemyType::Straight,
            dead: false,
        }
    }

    pub fn hitbox(&self) -> Rect {
        Rect::new(self.pos.x - 16.0, self.pos.y - 16.0, 32.0, 32.0)
    }
}

pub struct EnemyBullet {
    pub pos: Vec2,
    pub speed: f32,
    pub dead: bool,
}

impl EnemyBullet {
    pub fn new(x: f32, y: f32) -> Self {
        Self {
            pos: vec2(x, y),
            speed: 350.0,
            dead: false,
        }
    }

    pub fn hitbox(&self) -> Rect {
        Rect::new(self.pos.x - 4.0, self.pos.y - 4.0, 8.0, 8.0)
    }
}
