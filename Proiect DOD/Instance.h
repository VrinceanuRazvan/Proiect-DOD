#pragma once

#include "Vector2.h"
#include <SDL3/SDL.h>
#include <iostream>

class Instance
{
public:
	SDL_FRect rect;
	SDL_Color color = { 255, 0, 0, SDL_ALPHA_OPAQUE };
	Vector2 position;
	Vector2 size;
	float rotation = 0.0f;
public:
	Instance();

	Instance(Vector2 _position, Vector2 _size, float _rotation);

	void update();
	void render(SDL_Renderer* renderer);
};

