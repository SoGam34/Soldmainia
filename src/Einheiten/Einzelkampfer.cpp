#include "Einzelkampfer.h"

AbilityTyps Einzelkampfer::getAbility() const
{
	return Ability;
}

bool Einzelkampfer::checkIfWeaponCanBeEquipt(Waffen const& WeaponToCheck,
					     int const Kontostand) const
{
	return WeaponToCheck.getAbility() == Ability &&
	       WeaponToCheck.getBuyPrice() < Kontostand;
}

int Einzelkampfer::getSold(MissionTyps difficulty) const
{
	// TODO(EK): Implementieren der MEthode
	return 1;
}

std::string& Einzelkampfer::getÜbersichtsText()
{
	// TODO(EK): Implementieren der Methode
	OverviewText = "Some Discription";
	return OverviewText;
}