/*
 * Einheit.h
 *
 *  Created on: 26.04.2024
 *      Author: random
 */

#ifndef EINHEIT_H_
#define EINHEIT_H_

#include <string>

class Einheit {

	unsigned short int HP;
		unsigned short int Moral;
		unsigned short int Starke;
		unsigned short int Grosse;
		bool Einsatzbereit;
		std::string sName;
		unsigned int XP;
		unsigned int Level;

public:
	Einheit();
	Einheit(std::string name, unsigned short int hp = 100, unsigned short int moral = 10, unsigned short int starke = 1, bool einsatzbereit = true, unsigned short int grosse=1, unsigned int xp=1);

	virtual ~Einheit();
	Einheit(const Einheit &other);


	inline const std::string getName() const	{ return sName; }

	void XPHinzufugen(unsigned int newXP);
};

#endif /* EINHEIT_H_ */
