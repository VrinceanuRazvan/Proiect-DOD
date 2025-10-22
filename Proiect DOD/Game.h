#pragma once

#include <SDL3/SDL.h>
#include "Level.h"

class Game
{
private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	Level level;
public:
	//Creaza window si rendererul
	bool Init(int WINDOW_WIDTH = 640 ,int WINDOW_HEIGHT = 480);
	void RunLoop();
private:
	bool EventHandler();
	bool Update();
	bool Render();
};

	