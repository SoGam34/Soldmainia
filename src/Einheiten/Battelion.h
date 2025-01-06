#ifndef BATILION_H_
#define BATILION_H_

#include "Einheit.h"
class Battilion : public Einheit
{
	int MemberCount{1};

	int SoldPerMember{10};

	public:
	int getMemeberCount() const;

	int getSold() const;

	bool checkIfWeaponCanBeEquipt(Waffen const& WeaponToCheck,
				      int const Kontostand) const override;

	std::string& getÜbersichtsText() override;
};

#endif