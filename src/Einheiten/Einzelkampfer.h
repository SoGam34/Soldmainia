#ifndef EINZELKAMPFER_H_
#define EINZELKAMPFER_H_

#include "Einheit.h"
#include "Einheiten_CONST.h"
#include "Rüstung.h"
#include "Waffen.h"
#include <string>

class Einzelkampfer : public Einheit
{

	AbilityTyps Ability;

	public:
	Einzelkampfer() = delete;
	Einzelkampfer(AbilityTyps const Ability, int const BasisDealingDamage, int const BasisProtaction,
			  int const minExpierienceForLevelUpgrade, std::string const& name);
	AbilityTyps getAbility() const;

	bool checkIfWeaponCanBeEquipt(Waffen const& WeaponToCheck, int const Kontostand) const override;

	int getSold(MissionTyps difficulty) const;

	std::string& getÜbersichtsText() override;
};

#endif