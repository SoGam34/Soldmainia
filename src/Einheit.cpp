/*
 * Einheit.cpp
 *
 *  Created on: 26.04.2024
 *      Author: random
 */

#include "Einheit.h"

Einheit::Einheit(std::string name, unsigned short int hp = 100,
		unsigned short int moral = 10, unsigned short int starke = 1,
		bool einsatzbereit = true, unsigned short int grosse = 1,
		unsigned int xp = 1)
{
	Name = name;
	HP = hp;
	Moral = moral;
	Starke = starke;
	Einsatzbereit = einsatzbereit;
	Grosse = grosse;
	XP = xp;
	Level = 0;
}

Einheit::~Einheit()
{
	// TODO Auto-generated destructor stub
}

void Einheit::xpHinzufugen(unsigned int newXP)
{
	XP += newXP;
	if (XP / XPfuerLevelAufstieg >= 1)
	{
		Level += XP / XPfuerLevelAufstieg;
		XPfuerLevelAufstieg *= XP_FACTOR;
	}
}
