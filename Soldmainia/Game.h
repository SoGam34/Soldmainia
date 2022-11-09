#pragma once
#include "Data.h"
#include "Batilion_Ausbildungszentrum.h"
#include "Scoutb�ro.h"
#include "Auswahl.h"

class Game
{
public:
	//Konstruktor 
	Game();
	~Game();
	//Update loop
	void SpielLauft();

private:
	//window
	sf::RenderWindow* window;

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
	sf::Text sfText;

	sf::Clock clTagesTimer;
	int iTag;

	Data* myData;
	Auswahl* cAuswahl;
	Scoutb�ro* cScoutb�ro;

	//Gebaude
	//BAZ
	Batilion_Ausbildungszentrum* cBAZ;

	//Funktionen
	void update();
	int updateButtons(int iOffset, int iAnzahlKacheln);
	void neuerTag();
	void mahlen();
	void mahlenText(std::string titel);

};

