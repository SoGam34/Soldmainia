#pragma once
#include "Timer.h"
#include "Data.h"

class Gebaeude : public Timer
{
public:
	//De/Konstrucktor
	Gebaeude(short int iHauptKachel, short int iProzessUpgradeReihe);
	Gebaeude(Data* data, short int iHauptKachel, short int UpgradeReihe);
	~Gebaeude();				  

	//Ausbildungs F.
	virtual std::stringstream ProzessText() = 0;
	virtual int ProzessKosten() = 0;
	virtual void EndeProzess() = 0;

	void StartProzess();			  
	void aktProzessZustand();

	// Upgrade Funktionen
	void UpgradeGeschwindikeit();
	void UpgradeKosten();

	//Sonstige Funktonen
	virtual void aktstd() = 0;		

	void BerrechnungVoraussichtlicheZeit();
	void updateTimer();					


	// Data zeiger																	//
	Data* cData;				 													//
	// Wenn true dann wird ein Batilion ausgebildet ansonsten ist es frei			//
	bool bProzessAktiv;																//
	// Gibt an wie lange die Ausbildung vorausichtlich dauert 						//
	int iVoraussichtlicheZeit;														//
	// Der Ausbildungszeitversatz nachdem die Ausbildung wirklich beendet ist 		//
	int iZeitversatz;

private:
	short int iProzessHauptKachel;
	short int iProzessUpgradeReihe;
};

