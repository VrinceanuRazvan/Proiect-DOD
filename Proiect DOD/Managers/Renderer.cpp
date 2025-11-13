#include "Renderer.h"

namespace Renderer {
	SDL_Renderer* renderer = nullptr;

	SDL_Texture* entityTexture[100000];
	SpriteData* entitySpriteData[100000];
}

void Renderer::init(SDL_Renderer*& renderer, SDL_Window*& window, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
	for (int i = 0; i < 100000; i++) {
		entityTexture[i] = nullptr;
		entitySpriteData[i] = nullptr;
	}

	SDL_CreateWindowAndRenderer("Proiect DOD", WINDOW_WIDTH, WINDOW_HEIGHT, NULL, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	Renderer::renderer = renderer;
}

void Renderer::LoadEntityTexture(int id, const char* filePath, int frameCount, float frameDuration)
{
	SDL_Surface* surface = SDL_LoadBMP(filePath);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	int frameWidth = surface->w / frameCount;
	int frameHeight = surface->h;

	SDL_DestroySurface(surface);
	entityTexture[id] = texture;
	entitySpriteData[id] = new SpriteData(frameCount, frameWidth, frameHeight, frameDuration);
}

void Renderer::RenderEntities(SDL_Renderer* renderer, Entity* (&entityArray)[100000], float deltaTime ,bool isDOD)
{
	for (int i = 0; i < 100000; i++) {
		if (entitySpriteData[i] != nullptr) {
			if (isDOD)
				RenderEntityDOD(renderer, i, deltaTime);
			else
				RenderEntityOOP(renderer, entityArray[i], deltaTime);
		}
	}
}

void Renderer::RenderEntityOOP(SDL_Renderer* renderer, Entity* entity, float deltaTime)
{
	entitySpriteData[entity->GetId()]->UpdateAnimation(deltaTime);

	SDL_Texture* texture = entityTexture[entity->GetId()];
	if (texture == nullptr) return;

	const SpriteData& spriteData = *entitySpriteData[entity->GetId()];

	DrawSprite(renderer, texture, entity->getPosition(), spriteData);
}

void Renderer::RenderEntityDOD(SDL_Renderer* renderer, int i, float deltaTime)
{
	entitySpriteData[i]->UpdateAnimation(deltaTime);

	SDL_Texture* texture = entityTexture[i];
	if (texture == nullptr) return;

	const SpriteData& spriteData = *entitySpriteData[i];

	DrawSprite(renderer, texture, EntityManager::entityPositions[i], spriteData);
}

void Renderer::DrawSprite(SDL_Renderer* renderer, SDL_Texture* texture, Vector2 pos, const SpriteData& spriteData)
{
	if (texture == nullptr) return;

	SDL_FRect srcRect;
	srcRect.x = spriteData.currentFrame * spriteData.frameWidth;
	srcRect.y = 0;
	srcRect.w = static_cast<float>(spriteData.frameWidth);
	srcRect.h = static_cast<float>(spriteData.frameHeight);

	SDL_FRect dstRect;
	dstRect.x = pos.x - (spriteData.frameWidth / 2.0f);
	dstRect.y = pos.y - (spriteData.frameHeight / 2.0f);
	dstRect.w = static_cast<float>(spriteData.frameWidth);
	dstRect.h = static_cast<float>(spriteData.frameHeight);

	SDL_RenderTexture(renderer, texture, &srcRect, &dstRect);
}
