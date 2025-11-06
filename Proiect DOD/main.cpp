#include "Classes/Game.h"

int main(int argc, char* argv[])
{
	Game game;

	bool ceva = game.Init(1280,680);

	while (1)
	{
		game.RunLoop();
	}
	return 1;
}