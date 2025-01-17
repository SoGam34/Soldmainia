#include "Rüstung.h"
#include <sstream>

int Rüstung::getProtaction() const {
      return Protaction;
}

std::string Rüstung::getDiscriptionText() {
      std::stringstream sss;
      std::stringstream sab;
      if (Ability != AbilityTyps::none) {
            // TODO(Waffen): Adding Ability Discription
      }

      sss << "The Weapon " << Name << " has: \n Damage: " << Protaction << "\n";

      return sss.str();
}