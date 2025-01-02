/*
 * Einheit.cpp
 *
 *  Created on: 26.04.2024
 *      Author: random
 */

#include "Einheit.h"

#include <utility>

Einheit::Einheit(std::string& name, unsigned short int hp,
		 unsigned short int moral, unsigned short int starke,
		 bool einsatzbereit, unsigned short int grosse, unsigned int xp)
    : HP(hp), Moral(moral), Starke(starke), Einsatzbereit(einsatzbereit),
      Name(name), XP(xp), Level(0)
{

	grosse = grosse;
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
