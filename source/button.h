#pragma once
#include "../source/gameObject.h"   
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/textures.h"
#include "../source/globals.h"
#include "../source/textObject.h"

class Button {
public:
    
    SDL_FRect sprite;
    float r, g, b = 0.f;
    float opacity = SDL_ALPHA_OPAQUE_FLOAT;
    void (*OnClick)();

    const char* emptyString = "";

    TextObject<const char*> msg {
        "Message: %s", 0.f, 0.f,
        0.f, 0.f, 255, 255, 255, emptyString
    };


    Button(float x, float y, float w, float h,
        void (*OnClickFunction)(),
        float rVal, float gVal, float bVal, const char* text);

    bool CheckHover();
    void Render();
};
