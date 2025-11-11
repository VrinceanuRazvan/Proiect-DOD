#include "Game.h"

namespace Game {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	int WINDOW_WIDTH = 1280;
	int WINDOW_HEIGHT = 1080;

	bool isDOD = false;
}

void Game::init()
{
	Renderer::init(renderer, window, WINDOW_WIDTH, WINDOW_HEIGHT);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer3_Init(renderer);

	EntityManager::init();
	Clock::init();

	std::cout << EntityManager::spawnRate << std::endl;
}

void Game::RunLoop()
{
	Clock::Update();

	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Entity Spawner");
	ImGui::Text("FPS: %.1f (%.2f ms/frame)", 1.0f / Clock::deltaTime, 1000.0f * Clock::deltaTime);
	ImGui::Checkbox("Auto Spawn", &EntityManager::autoSpawn);
	ImGui::Text("Mode: %s", isDOD ? "DOD" : "OOP");
	if (ImGui::Button("Switch Mode")) {
		Switch();
	}
	ImGui::SliderFloat("Spawn Rate (per second)", &EntityManager::spawnRate, 0.0f, 1000.0f);
	ImGui::Text("Entity Count: %d", EntityManager::entityCount);
	ImGui::End();

	EventHandler();

	Update(Clock::deltaTime);

	Render(Clock::deltaTime);
}

void Game::Switch()
{
	isDOD = !isDOD;
	EntityManager::Switch(isDOD);
}

void Game::EventHandler()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
		ImGui_ImplSDL3_ProcessEvent(&event);
		if (event.type == SDL_EVENT_QUIT) {
			exit(0);
		}
}

void Game::Update(float deltaTime)
{
	EntityManager::update(deltaTime, isDOD);

	PhysicalManager::Update(deltaTime,isDOD);
}

void Game::Render(float deltaTime)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	Renderer::RenderEntities(renderer, EntityManager::entityArray, deltaTime, isDOD);

	ImGui::Render();
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

	SDL_RenderPresent(renderer);
}
