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

    Button(float x, float y, float w, float h,
        void (*OnClickFunction)(), 
        float rVal, float gVal, float bVal) {
        sprite = SDL_FRect{ x,y,w,h };
        OnClick = OnClickFunction;
        r = rVal;
        g = gVal;
        b = bVal;
    }

    void CheckHover() {
        SDL_PumpEvents();

        float mouseY;
        float mouseX;
       

        SDL_MouseButtonFlags MouseState = SDL_GetMouseState(&mouseX, &mouseY);

        if (mouseX >= sprite.x && mouseX <= sprite.x + sprite.w &&
            mouseY >= sprite.y && mouseY <= sprite.y + sprite.h)
        {
            OnClick();
            opacity = 0.f;
            SDL_HideCursor();;
        }

    };
    void Render() {

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColorFloat(renderer, r, g, b, opacity);
        SDL_RenderFillRect(renderer, &sprite);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    };
};
