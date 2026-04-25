use macroquad::prelude::*;

pub struct Player {
    pub pos: Vec2,
    pub speed: f32,
}

impl Player {
    pub fn new() -> Self {
        Self {
            pos: vec2(200.0, 360.0),
            speed: 300.0,
        }
    }

    pub fn update(&mut self, dt: f32) {
        if is_key_down(KeyCode::Left) {
            self.pos.x -= self.speed * dt;
        }
        if is_key_down(KeyCode::Right) {
            self.pos.x += self.speed * dt;
        }
        if is_key_down(KeyCode::Up) {
            self.pos.y -= self.speed * dt;
        }
        if is_key_down(KeyCode::Down) {
            self.pos.y += self.speed * dt;
        }
    }

    pub fn draw(&self) {
        draw_circle(self.pos.x, self.pos.y, 15.0, YELLOW);
    }
}
