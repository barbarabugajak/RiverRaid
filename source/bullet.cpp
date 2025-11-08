#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/bullet.h"
#include "../source/textures.h"
#include "../source/globals.h"



bool Bullet::CheckBounds() {
    return ((sprite.y - sprite.h) < HEIGHT) && (sprite.y > 0.0f - sprite.h / 2);
}

void Bullet::Tick(float dt) {
    MoveY(-velY * speedY * dt);
}


