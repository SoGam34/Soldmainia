#ifndef WAFFEN_H_
#define WAFFEN_H_

#include "Einheiten_CONST.h"
#include "Gegenstand.h"
#include <string>
class Waffen : public Gegenstand
{
	int Damage;

	public:
	int getDamage() const;

	std::string getDiscriptionText() override;
};

#endif