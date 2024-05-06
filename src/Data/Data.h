#pragma once

#include <vector>

#include "../Einheit.h"

class Data
{
public:
	Data();

	~Data();

	std::vector<Einheit>& getEinheiten();

	void addEinheit(const Einheit &e);

	unsigned int getBekanntheit();

	void setBekanntheit(unsigned int value);

	int getKontostand();

	void abziehnVonKontostand(int betrag);

	void hinzufuegenZuKontostand(int betrag);

	void erhoheAnzahlTage();

	int getAnzahlTage();

	float getTagesDauer();

	void setTagesDauer(float neueDauer);

	const int getMONATS_DAUER() const;

	bool getImEinheitsAuswahlMenu();

	void setEinheitsAuswahlMenu(bool neuerStatus);

	void saveGameToFile();

private:

	//Geld
	int Kontostand = 1000000000;

	//Zeit
	int AnzahlTage;
	float TagesDauer;
	const int MONATS_DAUER = 30;

	bool ImEinheitsAuswahlMenu;

	//Einheiten
	unsigned int Bekantheit;
	std::vector<Einheit> Einheiten;
};
