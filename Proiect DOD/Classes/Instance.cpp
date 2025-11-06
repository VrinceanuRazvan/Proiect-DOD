#include "Instance.h"

Instance::Instance(Vector2 _position, float _radius)
{
	this->position = _position;
	this->radius = _radius;
	this->texture = nullptr;
}

bool Instance::LoadSpriteSheet(SDL_Renderer* renderer, const char* filepath, int frameCount, float frameDuration)
{
	SDL_Surface* surface = SDL_LoadBMP(filepath);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	int frameWidth = surface->w / frameCount;
	int frameHeight = surface->h;
	spriteData = SpriteData(frameCount, frameWidth, frameHeight, frameDuration);

	SDL_DestroySurface(surface);
	return true;
}

void Instance::UpdateAnimation(float deltaTime)
{
	spriteData.UpdateAnimation(deltaTime);
}

Vector2 Instance::getPosition() const
{
	return this->position;
}

float Instance::GetRadius() const
{
	return this->radius;
}

void Instance::setPosition(const Vector2 pos)
{
	this->position = pos;
}

SDL_Texture* Instance::GetTexture() const
{
	return this->texture;
}

const SpriteData& Instance::GetSpriteData() const
{
	return this->spriteData;
}