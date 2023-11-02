#pragma once
#include "Data.h"
#include "Batilion_Ausbildungszentrum.h"
#include "Scoutbuero.h"
#include "Traningszentrum.h"
#include "Zentale.h"
#include "Erholungsresort.h"
#include "Auswahl.h"
#include "View.h"
#include <thread>
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
		Hauptmenu, Zentrale, scoutbuero,
		Batillionsausbildungsstate, traningszentrum,
		Auftraege, AAuftraege, LogistikSystem,
		erholungsresort, EinzelMitglieder, Batillione
	};
	AktuellesMenu eAktuellesMenu;

	sf::Vector2i vMauspos;
	sf::Mouse cMouse;
	sf::Keyboard cKeyboard;

	sf::Clock clTagesTimer;
	int iTag;

	std::shared_ptr<Data> myData;

	std::unique_ptr<View> cView;

	bool bAuswahl;

	//Gebaude
	//BAZ
	Batillion_Ausbildungszentrum* cBAZ;

	//Scoutbuero
	Scoutbuero* cScoutbuero;

	//Trainingzentrum 
	Traningszentrum* cTraingzentrum;

	//Zentrale
	Zentale* cZentrale;

	//Erholungsresort
	Erholungsresort* cErholungsresort;

	std::mutex mSicherung;

	//std::vector<void> test;
	//Funktionen
	void TextAnzeigeinitzaliesieren();
	void update();
	int updateButtons(int iOffset, int iAnzahlKacheln);
	void checkSortcuts();
	void Zeit();
	void mahlen();
};