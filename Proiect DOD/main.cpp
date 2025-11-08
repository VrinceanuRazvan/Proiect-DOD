
#include "Classes/Game.h"


int main(int argc, char* argv[])
{
	Game::init();

	while (1)
	{
		Game::RunLoop();
	}

	return 1;
}