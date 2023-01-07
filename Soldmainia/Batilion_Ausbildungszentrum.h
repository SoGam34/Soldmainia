#pragma once
#include "Timer.h"
#include "Data.h"

class Batilion_Ausbildungszentrum : Timer
{
public:
	//De-/Konstrucktor
	Batilion_Ausbildungszentrum();
	Batilion_Ausbildungszentrum(Data* data);
	~Batilion_Ausbildungszentrum();

	//Ausbildungs F.
	std::stringstream AusbildungsText();
	void startAusbildung();
	void aktAusbildung();
	void Name();
	void EndeAusbildung();

	//Sonstige Funktonen
	void aktstd();
	void BerrechnungVoraussichtlicheZeit();
	void updateTimer();

	// Batilions Größe ändern
	void AnzahlErhohen();
	void AnzahlReduzieren();
	 
	// Upgrade Funktionen
	void upgrade();
	void UpgradeGeschwindikeit();
	void UpgradeGrundstarke();
	void UpgradeKosten();

private:
	// Data zeiger 
	Data *cData;	
	// Wenn true dann wird ein Batilion ausgebildet ansonsten ist es frei
	bool bAusbildungAktiv;		
	// Gibt an wie lange die Ausbildung vorausichtlich dauert
	int iVoraussichtlicheZeit;	 
	// Der Ausbildungszeitversatz nachdem die Ausbildung wirklich beendet ist 
	int iZeitversatz;	
	// Array zum speichern des aktuellen Levels
	int iLevel[3];
};
