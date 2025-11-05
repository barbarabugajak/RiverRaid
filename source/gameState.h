#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/textures.h"
#include "../source/globals.h"
#include "../source/bullet.h"
#include "../source/enemy.h"
#include <vector>


class GameState {

	public:
		std::vector<Enemy> Enemies;
		int score; 

};
