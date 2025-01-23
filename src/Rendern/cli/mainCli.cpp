#include <memory>
#include "../../Data/Data.h"
#include "../../Game.h"
#include "../View.h"
#include "Cli.h"

int main() {
      std::shared_ptr<Data> Daten = std::make_shared<Data>();

      View* v                     = new Cli(Daten);

      std::unique_ptr<Game> game  = std::make_unique<Game>(v, Daten);
      game->spielLauft();
      delete v;

      return 0;
}
