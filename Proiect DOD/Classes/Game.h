#pragma once

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include <imgui_impl_sdlrenderer3.h>

#include "../Managers/Renderer.h"
#include "../Managers/EntityManager.h"
#include "../Managers/PhysicsManager.h"

#include "../Utility/Clock.h"

namespace Game {
	extern SDL_Window* window;
	extern SDL_Renderer* renderer;

	extern int WINDOW_WIDTH;
	extern int WINDOW_HEIGHT;

	extern bool isDOD;

	void init();

	void RunLoop();

	void Switch();

	void EventHandler();
	void Update(float deltaTime);
	void Render(float deltaTime);
}

	