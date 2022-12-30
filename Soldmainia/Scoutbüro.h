#pragma once
#include "Gebaeude.h"
#include "Data.h"

class Scoutbüro : public Gebaeude
{
public:
	//De/Konstrucktor
	Scoutbüro();		
	Scoutbüro(Data* data);
	~Scoutbüro();		

	//Ausbildungs F.
	std::stringstream ProzessText() = 0;
	int ProzessKosten() = 0;
	void EndeProzess() = 0;

	void Annehmen();
	void Ablehnen();

	// Upgrade Funktionen
	void UpgradeRang();

	//Sonstige Funktonen
	void aktstd();

private:
	// Der mindest Rang den ein EM haben kann
	int iRangmin;
	// Die Mitarbeiterkosten der Suche 
	int iKostenmitarbeiter;
	// Für eine einfachere Verfaltung des der Suche und Erzeugung
	enum Rang { S = 7, A = 6, B = 5, C = 4, D = 3, E = 2, F = 1 };
	Rang eRang;
};

