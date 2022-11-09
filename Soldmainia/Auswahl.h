#pragma once
#include "Data.h"

class Auswahl
{
public:
	Auswahl();
	~Auswahl();
	// Erzeugen der Kacheln
	void AnzeigeVorbereitung();

	// Such Allgerhytmen
	void SucheNachEinsetzbarenEinheiten();

	void SucheNachVerletzten();

	void SucheNachTruppenmoral();

	void SucheNachStarke();

	void SucheNachKampfkraft();

	// Sortieren
	void up();

	void down();

	//Get/Set
	 std::string getEinheitsname(int ButtenID);

	void Testhin(std::string Text, int ID); 
	void print();

	void setData(Data* data);

private:
	std::vector <std::pair<std::string, int>> vAusgewahlten;
	Data* myData;
};

