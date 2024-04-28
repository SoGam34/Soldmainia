#pragma once
#include "Data.h"
#include "Batilion_Ausbildungszentrum.h"
#include "Scoutbuero.h"
#include "Traningszentrum.h"
#include "Zentale.h"
#include "Erholungsresort.h"
#include "Auswahl.h"
#include "View.h"
#include <chrono>
#include <memory>
#include <chrono>

class Game
{
public:
	//Konstruktor 
	Game();
	~Game();
	//Update loop
	void SpielLauft();

	//Allgemein
	enum Menus
	{
		Hauptmenu,
		zentrale,
		scoutbuero,
		Batillionsausbildungsstate,
		traningszentrum,
		Auftraege,
		AAuftraege,
		LogistikSystem,
		erholungsresort,
		EinzelMitglieder,
		Batillione
	};
	Menus AktuellesMenu;

	/*sf::Vector2i vMauspos;
	 sf::Mouse cMouse;
	 sf::Keyboard cKeyboard;

	 sf::Clock clTagesTimer;*/
	int Tag;

	std::chrono::time_point<std::chrono::steady_clock> LetzterTag;

	float TagesDauer;

	const int MONATS_DAUER = 30;

	std::shared_ptr<Data> Daten;

	std::unique_ptr<View> View;

	bool Auswahl;

	//Gebaude
	//BAZ
	Batillion_Ausbildungszentrum *BAZ;

	//Scoutbuero
	Scoutbuero *Scoutbueros;

	//Trainingzentrum 
	Traningszentrum *Traningzentren;

	//Zentrale
	Zentale *Zentrale;

	//Erholungsresort
	Erholungsresort *Erholungsresorts;

	//std::vector<void> test;
	//Funktionen
	void TextAnzeigeinitzaliesieren();
	void update();
	int updateButtons(int iOffset, int iAnzahlKacheln);
	void checkSortcuts();
	void zeit();
	void mahlen();
};
