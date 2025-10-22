#pragma once

#include "Entity.h"
#include <vector>

class Level
{
private:
	std::vector<Entity*> entities;
	std::vector<Entity*> entitiesToRemove; // pt alea care ies in afara ecranului
public:
	bool Init();

	void update();
	void render(SDL_Renderer* renderer);

	Entity* SpawnEntity(Vector2 position , Vector2 size , float roation);
};

