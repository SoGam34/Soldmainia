#pragma once
#include "Gebaeude.h"
#include "Auswahl.h"

class Erholungsresort : public Gebaeude, public Auswahl
{
public:
	Erholungsresort();
	Erholungsresort(Data* data);
	~Erholungsresort();

	std::stringstream ProzessText();
	int ProzessKosten();
	void EndeProzess();
	void AuswahlZuOrdnen(std::string Name);

	void aktstd();
};

