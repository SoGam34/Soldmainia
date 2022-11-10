#pragma once
#include "Data.h"
#include "Batilion_Ausbildungszentrum.h"
#include "Scoutbüro.h"
#include "Auswahl.h"
#include "View.h"

class Game
{
public:
	//Konstruktor 
	Game();
	~Game();
	//Update loop
	void SpielLauft();

private:
	//Allgemein
	enum AktuellesMenu
	{
		Hauptmenu, Zentrale, scoutbüro,
		Batilionsausbildungsstate, Träningszentrum,
		Aufträge, AAufträge, LogistikSystem,
		Erholungsresort, EinzelMitglieder, Batilione
	};
	AktuellesMenu eAktuellesMenu;

	sf::Vector2i vMauspos;
	sf::Mouse cMouse;
	sf::Keyboard cKeyboard;

	sf::Clock clTagesTimer;
	int iTag;

	Data* myData;
	Auswahl* cAuswahl;

	View* cView;

	//Gebaude
	//BAZ
	Batilion_Ausbildungszentrum* cBAZ;

	//Scoutbüro
	Scoutbüro* cScoutbüro;

	//Funktionen
	void update();
	int updateButtons(int iOffset, int iAnzahlKacheln);
	void neuerTag();
	void mahlen();
};