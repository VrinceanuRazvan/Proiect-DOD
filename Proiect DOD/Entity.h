#pragma once

#include "Instance.h"
#include <string.h>

class Entity : public Instance
{
private:
	std::string shape = "rectangle";
public:
	Entity(Vector2 position, Vector2 size, float rotation);
	void render(SDL_Renderer* renderer);
};

