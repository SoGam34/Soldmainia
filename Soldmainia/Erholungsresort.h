#pragma once
#include "Gebaeude.h"
#include "Auswahl.h"

class Erholungsresort : public Gebaeude
{
public:
	Erholungsresort();
	Erholungsresort(Data* data);
	~Erholungsresort();

	std::stringstream ProzessText();
	int ProzessKosten();
	void EndeProzess();

	void aktstd();
};

