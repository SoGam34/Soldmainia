#include <memory>
#include "../../Data/Data.h"
#include "../../Game.h"
#include "../View.h"
#include "tui.h"

int main() {
      std::shared_ptr<Data> Daten = std::make_shared<Data>();

      View* v                     = new Tui(Daten);

      std::unique_ptr<Game> game  = std::make_unique<Game>(v, Daten);
      game->spielLauft();

      delete v;
      return 0;
}
