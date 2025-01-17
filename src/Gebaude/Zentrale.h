#pragma once
#include "../Data/Data.h"
#include "../Timer.h"
#include "Gebaeude.h"

#include <memory>
#include <sstream>

class Zentrale {
     public:
      Zentrale() = delete;
      Zentrale(std::shared_ptr<Data>& data);

     private:
      std::shared_ptr<Data> Daten;
};
