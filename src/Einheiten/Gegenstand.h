#ifndef GEGENSTAND_H_
#define GEGENSTAND_H_

#include <string>
#include "Einheiten_CONST.h"
class Gegenstand {
     public:
      virtual ~Gegenstand() = default;
      std::string getName() const;

      AbilityTyps getAbility() const;

      int getSellPrice() const;
      int getBuyPrice() const;

      float getAbilityBoost() const;

      virtual std::string getDiscriptionText() = 0;

     protected:
      AbilityTyps Ability;

      int BuyPrice;
      int SellPrice;

      // The Boost is a Percentage
      float AbilityBoost;

      std::string Name;
};

#endif