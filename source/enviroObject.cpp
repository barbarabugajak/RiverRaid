#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/gameObject.h"
#include "../source/textures.h"
#include "../source/globals.h"
#include "../source/enviroObject.h"
#include <vector>



// Happens every game loop
void EnviroObject::Tick(float dt) {
	MoveY(velY * worldSpeed * dt);
}

bool EnviroObject::CheckBounds() {
	return (sprite.y < HEIGHT);
}
