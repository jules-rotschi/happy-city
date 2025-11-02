#include <io.h>
#include <fcntl.h>

#include "Game.h"

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	Game game;
	game.Init();
	game.Run();
}