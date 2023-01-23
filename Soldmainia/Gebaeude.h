#pragma once
#include "Timer.h"
#include "Data.h"

class Gebaeude : public Timer
{
public:
	//De/Konstrucktor
	Gebaeude(Data* data, unsigned short int iHauptKachel, unsigned short int KostenFaktor, unsigned short int ZeitFaktor);
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


	// Data zeiger
	Data* cData;	
	// Wenn true dann wird ein Batilion ausgebildet ansonsten ist es frei	
	bool bProzessAktiv;	
	// Gibt an wie lange die Ausbildung vorausichtlich dauert 				
	unsigned short int iVoraussichtlicheZeit;
	// Der Ausbildungszeitversatz nachdem die Ausbildung wirklich beendet ist 
	unsigned short int iZeitversatz;

	float iGeschwindikeitsFaktor;

	unsigned short int iKostenFaktor;

	unsigned short int iZeitFaktor;

	float fUpgradeKosten[3];

private:
	short int iProzessHauptKachel;
};

