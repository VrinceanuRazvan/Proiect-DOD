#pragma once

#include <SDL3/SDL.h>

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include <imgui_impl_sdlrenderer3.h>

#include "../Managers/Renderer.h"
#include "../Managers/EntityManager.h"
#include "../Managers/PhysicsManager.h"

namespace Game {
	extern SDL_Window* window;
	extern SDL_Renderer* renderer;

	extern int WINDOW_WIDTH;
	extern int WINDOW_HEIGHT;

	extern Uint64 lastFrameTime;
	extern float deltaTime;

	void init();

	void RunLoop();

	void EventHandler();
	void Update(float deltaTime);
	void Render(float deltaTime);

	void SpawnEntity(Vector2 pos);
	void SpawnEntityRandom();
}

	