#include "Gegenstand.h"

AbilityTyps Gegenstand::getAbility() const {
      return Ability;
}

int Gegenstand::getSellPrice() const {
      return SellPrice;
}
int Gegenstand::getBuyPrice() const {
      return BuyPrice;
}
float Gegenstand::getAbilityBoost() const {
      return AbilityBoost;
}

std::string Gegenstand::getName() const {
      return Name;
}
