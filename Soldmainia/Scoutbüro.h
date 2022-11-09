#pragma once
#include "Timer.h"
#include "Data.h"

class Scoutbüro : public Timer
{
public:
	//De/Konstrucktor
	Scoutbüro();
	Scoutbüro(Data* data);
	~Scoutbüro();

	//Ausbildungs F.
	std::stringstream SucheText();
	void startSuche();
	void aktSuche();
	void EndeSuche();
	void Annehmen();
	void Ablehnen();

	// Upgrade Funktionen
	void upgrade();
	void UpgradeGeschwindikeit();
	void UpgradeRang();
	void UpgradeKosten();

	//Sonstige Funktonen
	void aktstd();
	void BerrechnungVoraussichtlicheZeit();
	void updateTimer();

private:
	Data* cData;				// Data zeiger 
	bool bSucheAktiv;			// Wenn true dann wird ein Batilion ausgebildet ansonsten ist es frei
	int iVoraussichtlicheZeit;	// Gibt an wie lange die Ausbildung vorausichtlich dauert 
	int iZeitversatz;			// Der Ausbildungszeitversatz nachdem die Ausbildung wirklich beendet ist 
	int iRangmin;
	int iKostenmitarbeiter;
	enum Rang { S = 7, A = 6, B = 5, C = 4, D = 3, E = 2, F = 1 };
	Rang eRang;
};

