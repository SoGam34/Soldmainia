#pragma once


#include <vector>


#include "../Einheit.h"
#include "../Rendern/Kachel.h"

class Data
{
public:
	Data();

	~Data();

	Kachel& getHauptmenu(int pos);

	Kachel& getKacheln(int pos);

	std::vector<Einheit>& getEinheiten();

	void addEinheit(const Einheit& e);

	unsigned int getBekanntheit();

	void setBekanntheit(unsigned int value);

	int getKontostand();

	void setKontostand(int kontostand);

private:


	//Geld
	int Kontostand = 1000000000;

	//Einheiten
	unsigned int Bekantheit;
	std::vector<Einheit> Einheiten;

	Kachel aKacheln[28]
	{
		//Erste Reihe beginnt bei 70
		// Hauptmenu
		//					Text					PosTextX				PosTextY
		Kachel("Zentrale"					, 260, sf::Color::Black, sfFont, 15,					iAbstandthalter+15, 70, 1,					 iAbstandthalter, 70, iBreite, iHohe, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Batillionausbildungszentrum" , 260, sf::Color::Black, sfFont, 8 , 1 * iBreite + 2 * iAbstandthalter+15, 70, 2, 1 * iBreite + 2 * iAbstandthalter, 70, iBreite, iHohe, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Traeningszentrum"			, 260, sf::Color::Black, sfFont, 11, 2 * iBreite + 3 * iAbstandthalter+15, 70, 3, 2 * iBreite + 3 * iAbstandthalter, 70, iBreite, iHohe, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Scout Buero"					, 260, sf::Color::Black, sfFont, 10, 3 * iBreite + 4 * iAbstandthalter+15, 70, 4, 3 * iBreite + 4 * iAbstandthalter, 70, iBreite, iHohe, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		//zweite Reihe						  
		Kachel("Auftrage"					, 280 + iHohe , sf::Color::Black, sfFont, 3, 1 * iBreite + 2 * iAbstandthalter + 15, 70 + 1 * iAbstandthalter + iHohe, 6, 1 * iBreite + 2 * iAbstandthalter, 70 + 1 * iAbstandthalter + iHohe, iBreite, iHohe, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Aktive Auftrage"			, 280 + iHohe , sf::Color::Black, sfFont, 2, 2 * iBreite + 3 * iAbstandthalter + 15, 70 + 1 * iAbstandthalter + iHohe, 7, 2 * iBreite + 3 * iAbstandthalter, 70 + 1 * iAbstandthalter + iHohe, iBreite, iHohe, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Logistik System"			, 280 + iHohe , sf::Color::Black, sfFont, 9, 3 * iBreite + 4 * iAbstandthalter + 15, 70 + 1 * iAbstandthalter + iHohe, 8, 3 * iBreite + 4 * iAbstandthalter, 70 + 1 * iAbstandthalter + iHohe, iBreite, iHohe, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Erholungsresort"			, 280 + iHohe , sf::Color::Black, sfFont, 7, iAbstandthalter + 15					, 70 + 1 * iAbstandthalter + iHohe, 5, 					 iAbstandthalter, 70 + 1 * iAbstandthalter + iHohe, iBreite, iHohe, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),

		//BAZ
		Kachel("Neues Batillion Ausbilden\nGr��e: 10\nKampfkraft: 1000" , 200, sf::Color::Black, sfFont, 99,	1*iAbstandthalter				, 95, 9 ,					 iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Beschleunigt die\nAusbildungsdauer um 5%\n Kosten 100" , 350, sf::Color::Black, sfFont,  4, 1 * iBreite + 2 * iAbstandthalter+15, 95, 10, 1 * iBreite + 2 * iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Erhoehung der Grundst�rke\nKosten 100"				   , 350, sf::Color::Black, sfFont,  6, 2 * iBreite + 3 * iAbstandthalter+15, 95, 11, 2 * iBreite + 3 * iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Reduzierung der Kosten\nKosten 100"	   				   , 350, sf::Color::Black, sfFont, 14, 3 * iBreite + 4 * iAbstandthalter+15, 95, 12, 3 * iBreite + 4 * iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
	
		//Scoutb�ro
		Kachel("Einselk�mpfer Rekutieren\n(EM)\nEin EM bekommt\nein Teil der Finanzellen\nBehlohnung und hat\neine Affinit�t.\nDie Affinit�t erlaubt\ndie Ausstatung spezieller\nWaffen und bringt\nVorteile bei bestimmten\nAuftragen.", 160, sf::Color::Black, sfFont, 99, iAbstandthalter,					95, 13,					    iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Beschleungigt die\nSuche um 5%\nKosten: 100"										 																																	, 350, sf::Color::Black, sfFont, 4, 1 * iBreite + 2 * iAbstandthalter+15, 95, 14, 1 * iBreite + 2 * iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Das Scoutb�ro\nfindet Einselkampfer die\neinen hohren Rang\nund Potenzial habne\nKosten: 100"														 																	, 350, sf::Color::Black, sfFont, 5, 2 * iBreite + 3 * iAbstandthalter+15, 95, 15, 2 * iBreite + 3 * iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Reduzierung der Kosten\nKosten: 100"														 																															, 350, sf::Color::Black, sfFont, 14,3 * iBreite + 4 * iAbstandthalter+15, 95, 16, 3 * iBreite + 4 * iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
	
	//Traningszentrum
 /*16*/ Kachel("Sie wahlen eine\nEinheit(Batillion/EM) aus,\nwelche im Zentrum\ntraniert wird,\ndadurch wird sie\nStarker und erhalt\nKampferfahrung was ein\nVorteil in Einsatzen\nist.", 160, sf::Color::Black, sfFont, 99, 1, 1, 1,				     iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Beschleungigt das\n Traning, bei\ngleicher Effektivit�t,\num 5%\nKosten: 100"										 													, 350, sf::Color::Black, sfFont, 99, 1, 1, 2, 1 * iBreite + 2 * iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Verbessert die Traningsmethoden wodurch die Effektivit�t ansteigt die Einheit wird noch starker und erhalt mehr erfahrung\nKosten: 100"									, 350, sf::Color::Black, sfFont, 99, 1, 1, 3, 2 * iBreite + 3 * iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Reduzierung der Traningskosten\nKosten: 100"														 																	, 350, sf::Color::Black, sfFont, 99, 1, 1, 3, 3 * iBreite + 4 * iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),

		//Zentrale
 /*20*/	Kachel("Sie wahlen eine\nEinheit(Batillion/EM) aus,\nwelche im Zentrum\ntraniert wird,\ndadurch wird sie\nStarker und erhalt\nKampferfahrung was ein\nVorteil in Einsatzen\nist.", 160, sf::Color::Black, sfFont, 99, 1, 1, 1,				     iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Beschleungigt das\n Traning, bei\ngleicher Effektivit�t,\num 5%\nKosten: 100"										 													, 350, sf::Color::Black, sfFont, 99, 1, 1, 2, 1 * iBreite + 2 * iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Verbessert die Traningsmethoden wodurch die Effektivit�t ansteigt die Einheit wird noch starker und erhalt mehr erfahrung\nKosten: 100"									, 350, sf::Color::Black, sfFont, 99, 1, 1, 3, 2 * iBreite + 3 * iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Reduzierung der Traningskosten\nKosten: 100"														 																	, 350, sf::Color::Black, sfFont, 99, 1, 1, 3, 3 * iBreite + 4 * iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),

		//Erholungsresort
 /*24*/	Kachel("Sie wahlen eine\nEinheit(Batillion/EM) aus,\nwelche sich dann\nVersorgt wird,\ndadurch steigen die\nErfolgsraten und\nUberlebenschance in\nEinsatzen verbessert.", 160, sf::Color::Black, sfFont, 99, 1, 1, 1,				     iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, 		 sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Beschleungigt das\n Traning, bei\ngleicher Effektivit�t,\num 5%\nKosten: 100"										 													, 350, sf::Color::Black, sfFont, 99, 1, 1, 2, 1 * iBreite + 2 * iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Verbessert die Traningsmethoden wodurch die Effektivit�t ansteigt die Einheit wird noch starker und erhalt mehr erfahrung\nKosten: 100"									, 350, sf::Color::Black, sfFont, 99, 1, 1, 3, 2 * iBreite + 3 * iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Reduzierung der Traningskosten\nKosten: 100"														 																	, 350, sf::Color::Black, sfFont, 99, 1, 1, 3, 3 * iBreite + 4 * iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),

	};

	
};
