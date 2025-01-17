#include "Waffen.h"
#include <sstream>
#include <string>
#include "Einheiten_CONST.h"

int Waffen::getDamage() const {
      return Damage;
}

std::string Waffen::getDiscriptionText() {
      std::stringstream ss;
      std::stringstream sab;
      if (Ability != AbilityTyps::none) {
            // TODO(Waffen): Adding Ability Discription
      }

      ss << "The Weapon " << Name << " has: \n Damage: " << Damage << "\n";

      return ss.str();
}
