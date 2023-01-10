#pragma once
#include "Data.h"
#include "Batilion_Ausbildungszentrum.h"
#include "Scoutbüro.h"
#include "Auswahl.h"
#include "View.h"
#include <thread>
#include <mutex>
#include <chrono>
#include <memory>
#include <mutex>

class Game
{
public:
	//Konstruktor 
	Game();
	~Game();
	//Update loop
	void SpielLauft();


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

	View* cView;


	//Gebaude
	//BAZ
	Batilion_Ausbildungszentrum* cBAZ;

	//Scoutbüro
	Scoutbüro* cScoutbüro;

	std::mutex mSicherung;

	//std::vector<void> test;
	//Funktionen
	void TextAnzeigeinitzaliesieren();
	void update();
	int updateButtons(int iOffset, int iAnzahlKacheln);
	void checkSortcuts();
	void neuerTag();
	void mahlen();
};