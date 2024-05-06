#pragma once
#include "../Data/Data.h"
#include "../Menus.cpp"

class View
{
public:
	//De/Konstrucktor
	View() = delete;
	View(std::shared_ptr<Data> data);
	~View();

	bool getSpielIstAktiv();

	int getLetzteNutzerEingabe();

	void ausgabe(Menus aktuellesMenu, GebaeudeStats stats);

	int einheitsAuswahlMenu();

	void ungueltigeEingabe(); //TODO: implementieren

private:

	void hilfsDialog();

	void printKopfZeile(std::string titel);

	void printFussZeile();

	void printGebaeudeStats(GebaeudeStats stats, std::string zeitText, std::string spzifischText, std::string kostenText);

	Menus ZuRenderndesMenu;

	int Eingabe;

	std::shared_ptr<Data> Daten;
};
