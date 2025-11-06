#pragma once

struct SpriteData
{
	int frameCount = 1;
	int currentFrame = 0;
	int frameWidth = 0;
	int frameHeight = 0;
	float animationTimer = 0.0f;
	float frameDuration = 0.1f;
	bool isAnimated = false;

	SpriteData() = default;

	SpriteData(int _frameCount, int _frameWidth, int _frameHeight, float _frameDuration = 0.1f)
		: frameCount(_frameCount), frameWidth(_frameWidth), frameHeight(_frameHeight),
		frameDuration(_frameDuration), isAnimated(_frameCount > 1)
	{
		currentFrame = 0;
		animationTimer = 0.0f;
	}

	void UpdateAnimation(float deltaTime)
	{
		if (!isAnimated || frameCount <= 1) return;

		animationTimer += deltaTime;
		if (animationTimer >= frameDuration)
		{
			animationTimer -= frameDuration;
			currentFrame = (currentFrame + 1) % frameCount;
		}
	}

	void Reset()
	{
		currentFrame = 0;
		animationTimer = 0.0f;
	}
};