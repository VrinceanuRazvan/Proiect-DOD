#include "Renderer.h"

void Renderer::RenderEntities(SDL_Renderer* renderer, Entity* (&entityArray)[100000], float deltaTime)
{
	for (int i = 0; i < 100000; i++) {
		if (entityArray[i] != nullptr) {
			RenderEntity(renderer, entityArray[i], deltaTime);
		}
	}
}

void Renderer::RenderEntity(SDL_Renderer* renderer, Entity* entity, float deltaTime)
{
	entity->UpdateAnimation(deltaTime);

	SDL_Texture* texture = entity->GetTexture();
	if (texture == nullptr) return;

	Vector2 position = entity->getPosition();
	const SpriteData& spriteData = entity->GetSpriteData();

	DrawSprite(renderer, texture, position, spriteData);
}

void Renderer::DrawSprite(SDL_Renderer* renderer, SDL_Texture* texture, Vector2 position, const SpriteData& spriteData)
{
	if (texture == nullptr) return;

	SDL_FRect srcRect;
	srcRect.x = spriteData.currentFrame * spriteData.frameWidth;
	srcRect.y = 0;
	srcRect.w = static_cast<float>(spriteData.frameWidth);
	srcRect.h = static_cast<float>(spriteData.frameHeight);

	SDL_FRect dstRect;
	dstRect.x = position.x - (spriteData.frameWidth / 2.0f);
	dstRect.y = position.y - (spriteData.frameHeight / 2.0f);
	dstRect.w = static_cast<float>(spriteData.frameWidth);
	dstRect.h = static_cast<float>(spriteData.frameHeight);

	SDL_RenderTexture(renderer, texture, &srcRect, &dstRect);
}