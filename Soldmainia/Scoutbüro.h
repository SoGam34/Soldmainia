#pragma once
#include "Timer.h"
#include "Data.h"

class Scoutbüro : public Timer
{
public:
	//De/Konstrucktor
	Scoutbüro();
	Scoutbüro(Data* data, std::mutex &mutex);
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
	// Data zeiger
	Data* cData;				 
	// Wenn true dann wird ein Batilion ausgebildet ansonsten ist es frei
	bool bSucheAktiv;			
	// Gibt an wie lange die Ausbildung vorausichtlich dauert 
	int iVoraussichtlicheZeit;	
	// Der Ausbildungszeitversatz nachdem die Ausbildung wirklich beendet ist 
	int iZeitversatz;		
	// Der mindest Rang den ein EM haben kann
	int iRangmin;
	// Die Mitarbeiterkosten der Suche 
	int iKostenmitarbeiter;
	// Für eine einfachere Verfaltung des der Suche und Erzeugung
	enum Rang { S = 7, A = 6, B = 5, C = 4, D = 3, E = 2, F = 1 };
	Rang eRang;
};

