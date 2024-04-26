/*
 * Einheit.h
 *
 *  Created on: 26.04.2024
 *      Author: random
 */

#ifndef EINHEIT_H_
#define EINHEIT_H_

#include <string>

class Einheit
{

	unsigned short int HP;
	unsigned short int Moral;
	unsigned short int Starke;
	unsigned short int Grosse;
	bool Einsatzbereit;
	std::string Name;
	unsigned int XP;
	unsigned int Level;
	unsigned int XPfuerLevelAufstieg = 100;
	const float XP_FACTOR = 1.3;

public:
	Einheit() = delete;
	Einheit(std::string name, unsigned short int hp = 100,
			unsigned short int moral = 10, unsigned short int starke = 1,
			bool einsatzbereit = true, unsigned short int grosse = 1,
			unsigned int xp = 1);

	virtual ~Einheit();

	inline const std::string getName() const
	{
		return Name;
	}

	inline const int getLeben() const
	{
		return HP;
	}

	inline const int getMoral() const
	{
		return Moral;
	}

	inline const int getStarke() const
	{
		return Starke;
	}

	inline const int getAnzahl() const
	{
		return Grosse;
	}

	inline const bool getEinsatzbereit() const
	{
		return Einsatzbereit;
	}

	inline const int getErfahrung() const
	{
		return XP;
	}

	inline const int getLevel() const
	{
		return Level;
	}

	void xpHinzufugen(unsigned int newXP);
};

#endif /* EINHEIT_H_ */
