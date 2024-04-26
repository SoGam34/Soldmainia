#pragma once
#include "Data/Data.h"

class Auswahl
{
public:
	Auswahl()=delete;
	Auswahl(std::shared_ptr<Data> data);
	~Auswahl();

	// Such Allgerhytmen
	void SucheNachEinsetzbarenEinheiten();

	void SucheNachVerletzten();

	void SucheNachTruppenmoral();

	void SucheNachStarke(int min);

	void SucheEinsetzbare_UND_GesundeEinheiten();

	void leeren();
	// Sortieren
	void SortiereNachStarke();

private:
	std::vector <int> vAusgewahlteEinheiten;
	std::shared_ptr<Data> Daten;

};

