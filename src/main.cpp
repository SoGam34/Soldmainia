#include "Data/Data.h"
#include "Game.h"
#include "Rendern/View.h"
#include <memory>

int main()
{
	std::shared_ptr<Data> Daten = std::make_shared<Data>();

	View* v = new View(Daten);

	std::unique_ptr<Game> game = std::make_unique<Game>(v, Daten);
	game->spielLauft();
	return 0;
}
