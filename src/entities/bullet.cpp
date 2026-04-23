#include "bullet.hpp"

Bullet::Bullet(float x, float y) {
    pos = {x, y};
}

void Bullet::update(float dt) {
    pos.x += speed * dt;
}

void Bullet::render() const {
    Rectangle r = hitbox();
    DrawRectangleRec(r, Color{255, 255, 100, 255});
}

Rectangle Bullet::hitbox() const {
    return { pos.x - size * 0.5f, pos.y - size * 0.5f, size, size };
}

bool Bullet::isOffscreen() const {
    return pos.x > GetScreenWidth() + size;
}
