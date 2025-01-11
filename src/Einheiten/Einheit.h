/**
 * @file Einheit.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-05-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef EINHEIT_H_
#define EINHEIT_H_

#include "Einheiten_CONST.h"
#include "Rüstung.h"
#include "Waffen.h"
#include <memory>
#include <string>

class Einheit
{
	Waffen PrimaryWeapon;
	Waffen SecondaryWeapon;

	Rüstung Armor;

	int HealtPoints{MAX_HEALTH_POINTS};
	int MentalPoints{MAX_MENTAL_POINTS};
	int Level{1};
	int BasisDealingDamage{1};
	int BasisProtaction{1};

	int minExpierienceForLevelUpgrade{10};
	int Expierience{0};

	std::string Name;

	bool Einsatzbereit{true};

	protected:
	std::string OverviewText;

	public:
	Einheit() = delete;
	Einheit(int const BasisDealingDamage, int const BasisProtaction, int const minExpierienceForLevelUpgrade,
		  std::string const& name);

	virtual ~Einheit() = default;
	Waffen& getPrimaryWeapon();
	Waffen& getSecondaryWeapon();
	Rüstung& getArmor();

	virtual bool checkIfWeaponCanBeEquipt(Waffen const& WeaponToCheck, int const Kontostand) const = 0;

	int getHealth() const;
	int getMental() const;
	int getLevel() const;
	std::string& getName();
	bool getReady() const;
	int getminExpierienceForLevelUpgrade() const;
	int getExpierience() const;
	int getTotalAmountOfDealingDamage() const;
	int getTotalAmountOfProtaction() const;

	void addExpierience(int const additionalExpierience);
	void addDamage(int const Damage);
	void recoverHealth(int const newHealthPoints);
	void recoverMental(int const newMentalPoints);
	void reduceMentalPonitsBy(int const amountToReduce);

	void equipPrimaryWeapon(Waffen const& WeaponToEquip);
	void equipSecondaryWeapon(Waffen const& WeaponToEquip);
	void equipArmor(Rüstung const& ArmorToEquip);

	virtual std::string& getÜbersichtsText() = 0;
};

#endif
