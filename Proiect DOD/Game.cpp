#include "Game.h"


bool Game::Init(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
	SDL_CreateWindowAndRenderer("Proiect DOD", WINDOW_WIDTH, WINDOW_HEIGHT, NULL, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	this->level.Init();
	return true;
}

void Game::RunLoop()
{
	this->EventHandler();
	this->Update();
	this->Render();
}

bool Game::EventHandler()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
		if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
			std::cout << "Click";
			float x, y;
			x = event.button.x;
			y = event.button.y;
			this->level.SpawnEntity(Vector2(x, y), Vector2(10, 10), 0.0f);
		}
	return true;
}

bool Game::Update()
{
	this->level.update();
	return true;
}

bool Game::Render()
{
	this->level.render(renderer);

	SDL_RenderPresent(renderer);
	return true;
}
