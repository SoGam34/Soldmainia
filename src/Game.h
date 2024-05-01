#pragma once
#include "Gebaude/Batilion_Ausbildungszentrum.h"
#include "Gebaude/Scoutbuero.h"
#include "Gebaude/Traningszentrum.h"
#include "Gebaude/Erholungsresort.h"
#include "Auswahl.h"
#include "Rendern/View.h"
#include <chrono>
#include <memory>
#include "Gebaude/Zentrale.h"
#include "Menus.cpp"

class Game
{
public:
	Game();
	~Game();

	void spielLauft();
private:

	void textAnzeigeinitzaliesieren();
		void update();
		int updateButtons(int iOffset, int iAnzahlKacheln);
		void checkSortcuts();
		void zeit();
		void mahlen();

	Menus AktuellesMenu;

	int AnzahlTage;

	std::chrono::time_point<std::chrono::steady_clock> ZeitpunktDesLetztenTages;

	float TagesDauer;

	const int MONATS_DAUER = 30;

	bool ImEinheitsAuswahlMenu;

	std::unique_ptr<View> View;

	std::shared_ptr<Data> Daten;

	Batillion_Ausbildungszentrum *BAZ;

	Scoutbuero *Scoutbueros;

	Traningszentrum *Traningzentren;

	Zentrale *Hauptquatier;

	Erholungsresort *Erholungsresorts;


};
