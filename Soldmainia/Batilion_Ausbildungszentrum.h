#pragma once
#include "Gebaeude.h"
#include "Data.h"

class Batilion_Ausbildungszentrum : public Gebaeude
{
public:
	//De-/Konstrucktor
	Batilion_Ausbildungszentrum();
	Batilion_Ausbildungszentrum(Data* data);
	~Batilion_Ausbildungszentrum();

	//Ausbildungs F.
	std::stringstream ProzessText();
	int ProzessKosten();
	void EndeProzess();

	void Name();

	//Sonstige Funktonen
	void aktstd();

	// Batilions Größe ändern
	void AnzahlErhohen();
	void AnzahlReduzieren();
	 
	// Upgrade Funktionen
	void UpgradeGrundstarke();
};

