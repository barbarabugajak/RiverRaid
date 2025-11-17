#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "../source/globals.h"
#include <iostream>

template <typename T>

class TextObject {
public:
	const char* text;
	char textBuffer[255];
	size_t bufferSize;
	T& param;
	SDL_Color color;
	SDL_FRect sprite;

	TextObject(const char* textVal, float x, float y, float w, float h, Uint8 r, Uint8 g, Uint8 b, T& paramValue) :
	param(paramValue)
	{
		text = textVal;
		sprite = SDL_FRect{ x, y, w, h };
		color = SDL_Color{ r,g,b };

		sprintf_s(textBuffer, text, param);
		
		bufferSize = strlen(textBuffer);
	}

	void UpdateText() {

		sprintf_s(textBuffer, text, param);

		bufferSize = strlen(textBuffer);
	}

	void Render() {

		UpdateText();

		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, textBuffer, bufferSize, color);
		SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		SDL_DestroySurface(surfaceMessage);
		SDL_RenderTexture(renderer, Message, NULL, &sprite);

		SDL_DestroyTexture(Message);
	}
};