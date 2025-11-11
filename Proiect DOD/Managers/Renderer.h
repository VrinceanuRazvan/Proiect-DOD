#pragma once
#include <SDL3/SDL.h>
#include "../Classes/Entity.h"
#include "../Utility/SpriteData.h"

#include "EntityManager.h" 

namespace Renderer {
	extern SDL_Renderer* renderer;
	extern SDL_Texture* entityTexture[100000];
	extern SpriteData* entitySpriteData[100000];

	void init(SDL_Renderer*& renderer, SDL_Window*& window,int WINDOW_WIDTH, int WINDOW_HEIGHT);

	void LoadEntityTexture(int id, const char* filePath, int frameCount = 1, float frameDuration = 0.1f);

	void RenderEntities(SDL_Renderer* renderer, Entity* (&entityArray)[100000], float deltaTime, bool isDOD);
	void RenderEntityOOP(SDL_Renderer* renderer, Entity* entity, float deltaTime);
	void RenderEntityDOD(SDL_Renderer* renderer, int i, float deltaTime);
	void DrawSprite(SDL_Renderer* renderer, SDL_Texture* texture, float positionX, float postionY, const SpriteData& spriteData);
}