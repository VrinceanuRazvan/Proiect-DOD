#pragma once
#include "../Utility/Vector2.h"
#include "../Utility/SpriteData.h"
#include <SDL3/SDL.h>
#include <iostream>

class Instance
{
public:
	Vector2 position;
	float radius = 0.0f;
	SDL_Texture* texture = nullptr;
	SpriteData spriteData;

public:
	Instance(Vector2 _position, float _radius);
	bool LoadSpriteSheet(SDL_Renderer* renderer, const char* filepath, int frameCount, float frameDuration = 0.1f);
	void UpdateAnimation(float deltaTime);

	Vector2 getPosition() const;
	float GetRadius() const;
	void setPosition(const Vector2 pos);
	SDL_Texture* GetTexture() const;
	const SpriteData& GetSpriteData() const;
};