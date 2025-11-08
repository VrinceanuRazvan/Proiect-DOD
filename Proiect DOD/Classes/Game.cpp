#include "Game.h"

namespace Game {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	int WINDOW_WIDTH = 640;
	int WINDOW_HEIGHT = 480;

	Uint64 lastFrameTime = SDL_GetTicks();
	float deltaTime = 0;
}

void Game::init()
{

	SDL_CreateWindowAndRenderer("Proiect DOD", WINDOW_WIDTH, WINDOW_HEIGHT, NULL, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer3_Init(renderer);

	EntityManager::init();

	std::cout << EntityManager::spawnRate << std::endl;
}

void Game::RunLoop()
{
	Uint64 currentTime = SDL_GetTicks();
	deltaTime = (currentTime - lastFrameTime) / 1000.0f;
	if (deltaTime > 0.05f) deltaTime = 0.05f;
	lastFrameTime = currentTime;

	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Entity Spawner");
	ImGui::Checkbox("Auto Spawn", &EntityManager::autoSpawn);
	ImGui::SliderFloat("Spawn Rate (per second)", &EntityManager::spawnRate, 0.0f, 100.0f);
	ImGui::Text("Entity Count: %d", EntityManager::entityCount);
	ImGui::End();

	EventHandler();

	Update(deltaTime);

	Render(deltaTime);
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
	EntityManager::update(renderer, deltaTime);

	for (int i = 0; i < EntityManager::entityCount; i++) {
		if (EntityManager::entityArray[i] != nullptr) {
			if (EntityManager::entityArray[i]->isStatic() == false) {

				PhysicalManager::moveToTarget(EntityManager::entityArray[i], Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT/2), deltaTime);

				for (int j = i + 1; j < EntityManager::entityCount; j++) {
					if (EntityManager::entityArray[j] != nullptr and EntityManager::entityArray[i] != EntityManager::entityArray[j]) {
						if (EntityManager::entityArray[j]->isStatic() == false) {
							collision col = PhysicalManager::find_colliion(EntityManager::entityArray[i]->getPosition(), EntityManager::entityArray[i]->GetRadius(),
								EntityManager::entityArray[j]->getPosition(), EntityManager::entityArray[j]->GetRadius());
							if (col.depth > 0.0f) {
								PhysicalManager::resolve_collision(col, EntityManager::entityArray[i], EntityManager::entityArray[j]);
							}
						}
					}
				}

				EntityManager::entityArray[i]->update(deltaTime);
			}
		}
	}
}

void Game::Render(float deltaTime)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	for (int i = 0; i < EntityManager::entityCount; i++) {
		if (EntityManager::entityArray[i] != nullptr) {
			Renderer::RenderEntity(renderer, EntityManager::entityArray[i], deltaTime);
		}
	}

	ImGui::Render();
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

	SDL_RenderPresent(renderer);
}

void Game::SpawnEntity(Vector2 pos)
{
	EntityManager::CreateEntity(pos ,renderer);
}

void Game::SpawnEntityRandom()
{
	Vector2 pos = Vector2(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT);
	SpawnEntity(pos);
}
