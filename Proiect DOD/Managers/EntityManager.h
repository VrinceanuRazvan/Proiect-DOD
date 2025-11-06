#pragma once
#include "../Classes/Entity.h"

void CreateEntity(Entity* (&entityArray)[100000],Vector2 pos, SDL_Renderer* renderer);
void DestroyEntity(Entity* (&entityArray)[100000], int indesx);