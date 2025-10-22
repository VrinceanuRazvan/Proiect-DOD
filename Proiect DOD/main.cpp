#include "Game.h"

void main(int argc, char* argv[])
{
	Game game;

	bool ceva = game.Init();

	while (1)
	{
		game.RunLoop();
	}
}