#include "Battelion.h"
#include "Einheit.h"
#include "Einheiten_CONST.h"
Battilion::Battilion(int const MemberCount,
                     int const BasisDealingDamage,
                     int const BasisProtaction,
                     int const minExpierienceForLevelUpgrade,
                     std::string const& name)
    : Einheit(BasisDealingDamage,
              BasisProtaction,
              minExpierienceForLevelUpgrade,
              name),
      MemberCount(MemberCount) {}
int Battilion::getMemeberCount() const {
      return MemberCount;
}

int Battilion::getSold() const {
      return SoldPerMember * MemberCount;
}

bool Battilion::checkIfWeaponCanBeEquipt(Waffen const& WeaponToCheck,
                                         int const Kontostand) const {
      return WeaponToCheck.getAbility() == AbilityTyps::none &&
             WeaponToCheck.getBuyPrice() * MemberCount < Kontostand;
}

std::string& Battilion::getÜbersichtsText() {
      // TODO(Battilion): Implementieren der Methode
      OverviewText = "Some Discription";
      return OverviewText;
}
