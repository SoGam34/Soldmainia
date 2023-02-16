#include "Game.h"

int main()
{
	Game cGame;
	//std::thread worker(&Game::TextAnzeigeinitzaliesieren, cGame);
	//worker.join();
	cGame.SpielLauft();
	return 0;
}