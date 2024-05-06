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
	Einheit(std::string name, unsigned short int hp,
			unsigned short int moral, unsigned short int starke,
			bool einsatzbereit, unsigned short int grosse,
			unsigned int xp);

	virtual ~Einheit();

	inline std::string getName() const
	{
		return Name;
	}

	inline int getLeben() const
	{
		return HP;
	}

	inline int getMoral() const
	{
		return Moral;
	}

	inline int getStarke() const
	{
		return Starke;
	}

	inline int getAnzahl() const
	{
		return Grosse;
	}

	inline bool getEinsatzbereit() const
	{
		return Einsatzbereit;
	}

	inline int getErfahrung() const
	{
		return XP;
	}

	inline int getLevel() const
	{
		return Level;
	}

	void xpHinzufugen(unsigned int newXP);
};

#endif /* EINHEIT_H_ */
