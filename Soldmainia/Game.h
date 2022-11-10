#pragma once
#include "Data.h"
#include "Batilion_Ausbildungszentrum.h"
#include "Scoutb�ro.h"
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
		Hauptmenu, Zentrale, scoutb�ro,
		Batilionsausbildungsstate, Tr�ningszentrum,
		Auftr�ge, AAuftr�ge, LogistikSystem,
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

	//Scoutb�ro
	Scoutb�ro* cScoutb�ro;

	//Funktionen
	void update();
	int updateButtons(int iOffset, int iAnzahlKacheln);
	void neuerTag();
	void mahlen();
};