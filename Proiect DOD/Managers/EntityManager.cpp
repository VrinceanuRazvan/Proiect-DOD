#include "EntityManager.h"

void CreateEntity(Entity* (&entityArray)[100000],Vector2 position, SDL_Renderer* renderer)
{
    for (int i = 0; i < 100000; i++) {
        if (entityArray[i] == nullptr) {
            entityArray[i] = new Entity(position);
			entityArray[i]->LoadSpriteSheet(renderer, "./Sprites/knight idle.bmp",4);
            return;
        }
    }
}

void DestroyEntity(Entity* (&entityArray)[100000], int index)
{
}