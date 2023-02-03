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
		Hauptmenu, Zentrale, scoutbuero,
		Batilionsausbildungsstate, traningszentrum,
		Auftraege, AAuftraege, LogistikSystem,
		erholungsresort, EinzelMitglieder, Batilione
	};
	AktuellesMenu eAktuellesMenu;

	sf::Vector2i vMauspos;
	sf::Mouse cMouse;
	sf::Keyboard cKeyboard;

	sf::Clock clTagesTimer;
	int iTag;

	Data* myData;

	View* cView;

	bool bAuswahl;

	//Gebaude
	//BAZ
	Batilion_Ausbildungszentrum* cBAZ;

	//Scoutb�ro
	Scoutbuero* cScoutbuero;

	//Trainingzentrum 
	Traningszentrum* cTraingzentrum;

	//Zentrale
	Zentale* cZentrale;

	//Erholungsresort
	Erholungsresort* cErholungsresort;

	//Funktionen
	void TextAnzeigeinitzaliesieren();
	void update();
	int updateButtons(int iOffset, int iAnzahlKacheln);
	void checkSortcuts();
	void neuerTag();
	void mahlen();
};