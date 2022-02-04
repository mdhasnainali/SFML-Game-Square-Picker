#include <iostream>
#include "Game.h"

using namespace std;


int main()
{
	//Init game engine
	Game game;

	while (game.running() && !game.getGameEnd())
	{

		game.update();
		game.render();
	}

}
