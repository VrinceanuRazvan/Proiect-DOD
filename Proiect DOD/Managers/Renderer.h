#pragma once
#include <SDL3/SDL.h>
#include "../Classes/Entity.h"
#include "../Utility/SpriteData.h"

void RenderEntities(SDL_Renderer* renderer, Entity* (&entityArray)[100000], float deltaTime);
void RenderEntity(SDL_Renderer* renderer, Entity* entity, float deltaTime);
void DrawSprite(SDL_Renderer* renderer, SDL_Texture* texture, Vector2 position, const SpriteData& spriteData);