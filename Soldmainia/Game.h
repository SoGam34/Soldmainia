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
		Hauptmenu, Zentrale, scoutbuero,
		Batilionsausbildungsstate, Traeningszentrum,
		Auftraege, AAuftraege, LogistikSystem,
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
	sf::Event event;
	View* cView;

	//Gebaude
	//BAZ
	Batilion_Ausbildungszentrum* cBAZ;

	//Scoutbuero
	Scoutbuero* cScoutbuero;

	//Funktionen
	void TextAnzeigeinitzaliesieren();
	void update();
	int updateButtons(int iOffset, int iAnzahlKacheln);
	void checkSortcuts();
	void neuerTag();
	void mahlen();
};