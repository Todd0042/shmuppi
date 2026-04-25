use macroquad::prelude::*;

pub struct Enemy {
    pub pos: Vec2,
    pub speed: f32,
}

impl Enemy {
    pub fn new() -> Self {
        let y = rand::gen_range(40.0, screen_height() - 40.0);
        Self {
            pos: vec2(screen_width() + 40.0, y),
            speed: 150.0,
        }
    }

    pub fn update(&mut self, dt: f32) {
        self.pos.x -= self.speed * dt;
    }

    pub fn draw(&self) {
        draw_circle(self.pos.x, self.pos.y, 15.0, RED);
    }

    pub fn offscreen(&self) -> bool {
        self.pos.x < -40.0
    }
}
