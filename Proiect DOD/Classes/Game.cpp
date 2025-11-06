#include "Game.h"


bool Game::Init(int WINDOW_WIDTH = 640, int WINDOW_HEIGHT = 480)
{
	this->WINDOW_WIDTH = WINDOW_WIDTH;
	this->WINDOW_HEIGHT = WINDOW_HEIGHT;
	SDL_CreateWindowAndRenderer("Proiect DOD", WINDOW_WIDTH, WINDOW_HEIGHT, NULL, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	this->lastFrameTime = SDL_GetTicks();

	for (int i = 0; i < 100000; i++) {
		entityArray[i] = nullptr;
	}

	return true;
}

void Game::RunLoop()
{
	Uint64 currentTime = SDL_GetTicks();
	float deltaTime = (currentTime - this->lastFrameTime) / 1000.0f;
	if (deltaTime > 0.05f) deltaTime = 0.05f;
	this->lastFrameTime = currentTime;

	this->EventHandler();
	this->Update(deltaTime);
	this->Render(deltaTime);
}

bool Game::EventHandler()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
		if (event.type == SDL_EVENT_QUIT) {
			exit(0);
		}
		else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
			SpawnEntity(Vector2(event.button.x, event.button.y));
			entityCount++;
		}
	return true;
}

bool Game::Update(float deltaTime)
{
	for (int i = 0; i < entityCount; i++) {
		if (entityArray[i] != nullptr) {
			if (entityArray[i]->isStatic() == false) {

				moveToTarget(entityArray[i], Vector2(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f), 100.0f, deltaTime);

				for (int j = i + 1; j < entityCount; j++) {
					if (entityArray[j] != nullptr and entityArray[i] != entityArray[j]) {
						if (entityArray[j]->isStatic() == false) {
							collision col = find_colliion(entityArray[i]->getPosition(), entityArray[i]->GetRadius(),
								entityArray[j]->getPosition(), entityArray[j]->GetRadius());
							if (col.depth > 0.0f) {
								resolve_collision(col, entityArray[i], entityArray[j]);
							}
						}
					}
				}

				entityArray[i]->update(deltaTime);
			}
		}
	}

	return true;
}

bool Game::Render(float deltaTime)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	for (int i = 0; i < entityCount; i++) {
		if (entityArray[i] != nullptr) {
			RenderEntity(renderer, entityArray[i], deltaTime);
		}
	}

	SDL_RenderPresent(renderer);
	return true;
}

void Game::SpawnEntity(Vector2 pos)
{
	CreateEntity(entityArray,pos ,renderer);
}