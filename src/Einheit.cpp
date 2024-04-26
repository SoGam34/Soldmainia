/*
 * Einheit.cpp
 *
 *  Created on: 26.04.2024
 *      Author: random
 */

#include "Einheit.h"

Einheit::Einheit() {
	// TODO Auto-generated constructor stub

}

Einheit::Einheit(std::string name, unsigned short int hp = 100, unsigned short int moral = 10, unsigned short int starke = 1, bool einsatzbereit = true, unsigned short int grosse=1, unsigned int xp=1)
	{
		sName = name;
		HP = hp;
		Moral = moral;
		Starke = starke;
		Einsatzbereit = einsatzbereit;
		Grosse = grosse;
		XP = xp;
		Level = 0;
	}

Einheit::~Einheit() {
	// TODO Auto-generated destructor stub
}

Einheit::Einheit(const Einheit &other) {
	// TODO Auto-generated constructor stub

}

void Einheit::XPHinzufugen(unsigned int newXP)
	{
		XP+=newXP;
		if(XP/100>0)
		{
			Level+=XP/100;
		}
	}
