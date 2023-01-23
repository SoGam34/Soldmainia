#pragma once
#include "Gebaeude.h"
#include "Data.h"

class Batilion_Ausbildungszentrum : public Gebaeude
{
public:
	//De-/Konstrucktor
	Batilion_Ausbildungszentrum(Data* data);
	~Batilion_Ausbildungszentrum();

	//Ausbildungs F.
	std::stringstream ProzessText();
	int ProzessKosten();
	void EndeProzess();

	void Vorbereiten_neueAusbildung();

	//Sonstige Funktonen
	void aktstd();

	// Batilions Gr��e �ndern
	void AnzahlErhohen();
	void AnzahlReduzieren();
	 
	// Upgrade Funktionen
	void UpgradeGrundstarke();

private:
	unsigned short int iBekanntheit = 1;
	unsigned short int iBatilonsgr��e = 10;
	unsigned short int iKostenproKopf = 70;
	float fGrundst�rke = 10;
};

