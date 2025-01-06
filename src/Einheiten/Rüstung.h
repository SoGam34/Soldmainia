#ifndef RÜSTUNG_H_
#define RÜSTUNG_H_

#include "Einheiten_CONST.h"
#include "Gegenstand.h"
#include <string>
class Rüstung : public Gegenstand
{
	int Protaction;

	public:
	int getProtaction() const;

	std::string getDiscriptionText() override;
};

#endif
