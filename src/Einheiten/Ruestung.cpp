#include "Ruestung.h"
#include <sstream>

int Ruestung::getProtaction() const {
      return Protaction;
}

std::string Ruestung::getDiscriptionText() {
      std::stringstream sss;
      std::stringstream sab;
      if (Ability != AbilityTyps::none) {
            // TODO(Waffen): Adding Ability Discription
      }

      sss << "The Weapon " << Name << " has: \n Damage: " << Protaction << "\n";

      return sss.str();
}