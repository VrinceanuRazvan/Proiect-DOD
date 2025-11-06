#pragma once

#include <SDL3/SDL.h>
#include "../Managers/Renderer.h"
#include "../Managers/EntityManager.h"
#include "../Managers/PhysicsManager.h"

class Game
{
private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	Uint64 lastFrameTime = 0;

	int WINDOW_WIDTH = 640;
	int WINDOW_HEIGHT = 480;

	Entity* entityArray[100000];

	int entityCount = 0;

public:
	bool Init(int WINDOW_WIDTH,int WINDOW_HEIGHT);
	void RunLoop();
private:
	bool EventHandler();
	bool Update(float deltaTime);
	bool Render(float deltaTime);

	void SpawnEntity(Vector2 pos);
};

	