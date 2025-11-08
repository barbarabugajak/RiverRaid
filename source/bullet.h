#pragma once
#include "../source/gameObject.h"   
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/textures.h"
#include "../source/globals.h"

class Bullet : public GameObject {
public:
    using GameObject::GameObject;

    void Tick(float dt) override;
    bool CheckBounds();
};
