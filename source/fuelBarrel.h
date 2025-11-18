#pragma once
#include "../source/gameObject.h"   
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/textures.h"
#include "../source/globals.h"

class FuelBarrel : public GameObject {

public:

    using GameObject::GameObject;

    void Tick(float dt) override {
        std::cout << velY << std::endl;
        MoveY(velY * worldSpeed * dt);
    };
    bool CheckBounds() {
        return(sprite.y < HEIGHT);
    }
};
