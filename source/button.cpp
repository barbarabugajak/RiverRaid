#pragma once
#include "../source/gameObject.h"   
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../source/textures.h"
#include "../source/globals.h"
#include "../source/textObject.h"
#include "../source/button.h"


Button::Button(float x, float y, float w, float h,
        void (*OnClickFunction)(), 
        float rVal, float gVal, float bVal, const char* text) {
        sprite = SDL_FRect{ x,y,w,h };
        OnClick = OnClickFunction;
        r = rVal;
        g = gVal;
        b = bVal;
        msg.text = text;

        msg.sprite.w = sprite.w / 2.f;
        msg.sprite.h = sprite.h * 0.8f;
        msg.sprite.x = sprite.x + (sprite.w - msg.sprite.w) / 2.f;
        msg.sprite.y = sprite.y + (sprite.h - msg.sprite.h) / 2.f;


    }

bool Button::CheckHover() {
        SDL_PumpEvents();

        float mouseY;
        float mouseX;
       

        SDL_MouseButtonFlags MouseState = SDL_GetMouseState(&mouseX, &mouseY);

        if (mouseX >= sprite.x && mouseX <= sprite.x + sprite.w &&
            mouseY >= sprite.y && mouseY <= sprite.y + sprite.h)
        {
            OnClick();
            SDL_HideCursor();
            return true;
        }

        return false;
    };

void Button::Render() {

    if (opacity == 0) return;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColorFloat(renderer, r, g, b, opacity);
    SDL_RenderFillRect(renderer, &sprite);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    msg.UpdateText();
    msg.Render();
};
