use macroquad::prelude::*;

pub struct Bullet {
    pub pos: Vec2,
    pub speed: f32,
}

impl Bullet {
    pub fn new(x: f32, y: f32) -> Self {
        Self {
            pos: vec2(x, y),
            speed: 500.0,
        }
    }

    pub fn update(&mut self, dt: f32) {
        self.pos.x += self.speed * dt;
    }

    pub fn draw(&self) {
        draw_rectangle(self.pos.x, self.pos.y, 10.0, 4.0, WHITE);
    }

    pub fn offscreen(&self) -> bool {
        self.pos.x > screen_width()
    }
}
