#pragma once
#include "Kachel.h"
#include "Animationen.h"
#include <unordered_map>

struct Einheit
{
	unsigned short int HP;
	unsigned short int Moral;
	unsigned short int Starke;
	unsigned short int Grosse;
	bool Einsatzbereit;
	std::string sName;
	unsigned int XP;
	unsigned int Level;

	Einheit(std::string name, unsigned short int hp = 100, unsigned short int moral = 10, unsigned short int starke = 1, bool einsatzbereit = true, unsigned short int grosse=1, unsigned int xp=1)
	{
		sName = name;
		HP = hp;
		Moral = moral;
		Starke = starke;
		Einsatzbereit = einsatzbereit;
		Grosse = grosse;
		XP = xp;
		Level = 0;
	}

	void XPHinzufugen(unsigned int newXP)
	{
		XP+=newXP;
		if(XP/100>0)
		{
			Level+=XP/100;
		}
	}

	inline const std::string getName() const
	{
		return sName;
	}
};

class Data
{
public:
	Data()
	{
		sfFont.loadFromFile("Texturen/ArialCEMTBlack.ttf");

		cAnimationen.setFont(&sfFont);
		//BAZ
		aKacheln[11].addButten(3 * iAbstandthalter + 3 * iBreite + 35, 2 * iHohe + 50, 200, 30, 4, "Upgrade", &sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
		aKacheln[10].addButten(2 * iAbstandthalter + 2 * iBreite + 35, 2 * iHohe + 50, 200, 30, 3, "Upgrade", &sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
		aKacheln[9].addButten(1 * iAbstandthalter + 1 * iBreite + 35, 2 * iHohe + 50, 200, 30, 2, "Upgrade", &sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
		aKacheln[8].addButten(35, 450, 200, 30, 1, "Starten", &sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
		aKacheln[8].addButten(35, 350, 200, 30, 11, "Mehr Mitglieder", &sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
		aKacheln[8].addButten(35, 400, 200, 30, 12, "Weniger Mitglieder", &sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);

		//Scoutb�ro
		aKacheln[12].addButten(35, 450, 200, 30, 1, "Starten", &sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
		aKacheln[13].addButten(1 * iAbstandthalter + 1 * iBreite + 35, 450, 200, 30, 2, "Upgrade", &sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
		aKacheln[14].addButten(2 * iAbstandthalter + 2 * iBreite + 35, 450, 200, 30, 3, "Upgrade", &sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
		aKacheln[15].addButten(3 * iAbstandthalter + 3 * iBreite + 35, 450, 200, 30, 4, "Upgrade", &sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);

		//Trainingszentrum 
		aKacheln[16].addButten(45, 450, 200, 30, 5, "Lange Tranings Einheit", &sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
		aKacheln[16].addButten(45, 350, 200, 30, 6, "Kurze Trainings Einheit", &sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
		aKacheln[16].addButten(45, 400, 200, 30, 7, "Mittlere trainings Einheit", &sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
		aKacheln[17].addButten(1 * iAbstandthalter + 1 * iBreite + 45, 450, 200, 30, 2, "Upgrade", &sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
		aKacheln[18].addButten(2 * iAbstandthalter + 2 * iBreite + 45, 450, 200, 30, 3, "Upgrade", &sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
		aKacheln[19].addButten(3 * iAbstandthalter + 3 * iBreite + 45, 450, 200, 30, 4, "Upgrade", &sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
		
		umEinheiten.clear();

		Einheit e("Kai");
		Einheit r("Alina");
		Einheit d("Samantha");
		Einheit f("Lars");
		Einheit g("Tina");
		addEinheit( e);
		addEinheit( r);
		addEinheit( d);
		addEinheit( f);
		addEinheit( g);
	}
	~Data()
	{
		
	}

	Kachel& getHauptmenu(int pos)
	{
		return aKacheln[pos];
	}

	Kachel& getKacheln(int pos)
	{
		return aKacheln[pos];
	}

	Animationen& getAnimationen()
	{
		return cAnimationen;
	}

	std::vector<Einheit>& getEinheiten()
	{
		return umEinheiten;
	}

	const void addEinheit(const Einheit& const e)
	{
		umEinheiten.emplace_back(e);
	}

	unsigned int getBekanntheit()
	{
		return iBekanntheit;
	}

	void setBekanntheit(unsigned int value)
	{
		iBekanntheit = value;
	}

	sf::Font* getFont()
	{
		return &sfFont;
	}

	int getiKontostand()
	{
		return iKontostand;
	}

	void setiKontostand(int kontostand)
	{
		iKontostand = kontostand;
	}

	void setBenarichtigungAktiv()
	{
		bBenarichtigungAktiv = true;
	}

	bool getBenarichtigungAktiv()
	{
		return bBenarichtigungAktiv;
	}

private:

	//Kachel
	int iBreite = 230;
	int iHohe = 200;
	int iAbstandthalter = 20;
	sf::Font sfFont;

	//Geld
	int iKontostand = 1000000;

	// Animationen
	Animationen cAnimationen;
	bool bBenarichtigungAktiv = false;
	bool bUpgradeAnimation = false;

	//Einheiten
	unsigned int iBekanntheit;
	std::vector<Einheit> umEinheiten;

	Kachel aKacheln[28]
	{
		//Erste Reihe beginnt bei 70
		// Hauptmenu
		//					Text					PosTextX				PosTextY
		Kachel("Zentrale"					, 160, sf::Color::Black, &sfFont, 15, iAbstandthalter+15,				   	70, 1,					 iAbstandthalter, 70, iBreite, iHohe, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Batilionausbildungszentrum" , 160, sf::Color::Black, &sfFont, 8 , 1 * iBreite + 2 * iAbstandthalter+15, 70, 2, 1 * iBreite + 2 * iAbstandthalter, 70, iBreite, iHohe, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Tr�ningszentrum"			, 160, sf::Color::Black, &sfFont, 11, 2 * iBreite + 3 * iAbstandthalter+15, 70, 3, 2 * iBreite + 3 * iAbstandthalter, 70, iBreite, iHohe, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Scout B�ro"					, 160, sf::Color::Black, &sfFont, 10, 3 * iBreite + 4 * iAbstandthalter+15, 70, 4, 3 * iBreite + 4 * iAbstandthalter, 70, iBreite, iHohe, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		//zweite Reihe						  
		Kachel("Auftr�ge"					, 180 + iHohe , sf::Color::Black, &sfFont, 3, 1 * iBreite + 2 * iAbstandthalter + 15, 70 + 1 * iAbstandthalter + iHohe, 6, 1 * iBreite + 2 * iAbstandthalter, 70 + 1 * iAbstandthalter + iHohe, iBreite, iHohe, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Aktive Auftr�ge"			, 180 + iHohe , sf::Color::Black, &sfFont, 2, 2 * iBreite + 3 * iAbstandthalter + 15, 70 + 1 * iAbstandthalter + iHohe, 7, 2 * iBreite + 3 * iAbstandthalter, 70 + 1 * iAbstandthalter + iHohe, iBreite, iHohe, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Logistik System"			, 180 + iHohe , sf::Color::Black, &sfFont, 9, 3 * iBreite + 4 * iAbstandthalter + 15, 70 + 1 * iAbstandthalter + iHohe, 8, 3 * iBreite + 4 * iAbstandthalter, 70 + 1 * iAbstandthalter + iHohe, iBreite, iHohe, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Erholungsresort"			, 180 + iHohe , sf::Color::Black, &sfFont, 7, iAbstandthalter + 15					, 70 + 1 * iAbstandthalter + iHohe, 5, 					 iAbstandthalter, 70 + 1 * iAbstandthalter + iHohe, iBreite, iHohe, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		
		//BAZ
		Kachel("Neues Batilion Ausbilden\nGr��e: 10\nKampfkraft: 1000" , 200, sf::Color::Black, &sfFont, 99, 1, 1, 9 ,					 iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter				   , sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Beschleunigt die\nAusbildungsdauer um 5%\n Kosten 100" , 350, sf::Color::Black, &sfFont, 99, 1, 1, 10, 1 * iBreite + 2 * iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Erhoung der Grundst�rke\nKosten 100"				   , 350, sf::Color::Black, &sfFont, 99, 1, 1, 11, 2 * iBreite + 3 * iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Reduzierung der Kosten\nKosten 100"	   				   , 350, sf::Color::Black, &sfFont, 99, 1, 1, 12, 3 * iBreite + 4 * iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
	
		//Scoutb�ro
		Kachel("Einselk�mpfer Rekutieren\n(EM)\nEin EM bekommt\nein Teil der Finanzellen\nBehlohnung und hat\neine Affinit�t.\nDie Affinit�t erlaubt\ndie Ausstatung spezieller\nWaffen und bringt\nVorteile bei bestimmten\nAuftragen.", 160, sf::Color::Black, &sfFont, 99, 1, 1, 1,				     iAbstandthalter+15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Beschleungigt die\nSuche um 5%\nKosten: 100"										 																																	, 350, sf::Color::Black, &sfFont, 99, 1, 1, 2, 1 * iBreite + 2 * iAbstandthalter+15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Das Scoutb�ro\nfindet Einselkampfer die\neinen hohren Rang\nund Potenzial habne\nKosten: 100"														 																	, 350, sf::Color::Black, &sfFont, 99, 1, 1, 3, 2 * iBreite + 3 * iAbstandthalter+15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Reduzierung der Kosten\nKosten: 100"														 																															, 350, sf::Color::Black, &sfFont, 99, 1, 1, 3, 3 * iBreite + 4 * iAbstandthalter+15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
	
		//Traningszentrum
 /*16*/ Kachel("Sie wahlen eine\nEinheit(Batilion/EM) aus,\nwelche im Zentrum\ntraniert wird,\ndadurch wird sie\nStarker und erhalt\nKampferfahrung was ein\nVorteil in Einsatzen\nist.", 160, sf::Color::Black, &sfFont, 99, 1, 1, 1,				     iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Beschleungigt das\n Traning, bei\ngleicher Effektivit�t,\num 5%\nKosten: 100"										 													, 350, sf::Color::Black, &sfFont, 99, 1, 1, 2, 1 * iBreite + 2 * iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Verbessert die Traningsmethoden wodurch die Effektivit�t ansteigt die Einheit wird noch starker und erhalt mehr erfahrung\nKosten: 100"									, 350, sf::Color::Black, &sfFont, 99, 1, 1, 3, 2 * iBreite + 3 * iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Reduzierung der Traningskosten\nKosten: 100"														 																	, 350, sf::Color::Black, &sfFont, 99, 1, 1, 3, 3 * iBreite + 4 * iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),

		//Zentrale
 /*20*/	Kachel("Sie wahlen eine\nEinheit(Batilion/EM) aus,\nwelche im Zentrum\ntraniert wird,\ndadurch wird sie\nStarker und erhalt\nKampferfahrung was ein\nVorteil in Einsatzen\nist.", 160, sf::Color::Black, &sfFont, 99, 1, 1, 1,				     iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Beschleungigt das\n Traning, bei\ngleicher Effektivit�t,\num 5%\nKosten: 100"										 													, 350, sf::Color::Black, &sfFont, 99, 1, 1, 2, 1 * iBreite + 2 * iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Verbessert die Traningsmethoden wodurch die Effektivit�t ansteigt die Einheit wird noch starker und erhalt mehr erfahrung\nKosten: 100"									, 350, sf::Color::Black, &sfFont, 99, 1, 1, 3, 2 * iBreite + 3 * iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Reduzierung der Traningskosten\nKosten: 100"														 																	, 350, sf::Color::Black, &sfFont, 99, 1, 1, 3, 3 * iBreite + 4 * iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),

		//Erholungsresort
 /*24*/	Kachel("Sie wahlen eine\nEinheit(Batilion/EM) aus,\nwelche im Zentrum\ntraniert wird,\ndadurch wird sie\nStarker und erhalt\nKampferfahrung was ein\nVorteil in Einsatzen\nist.", 160, sf::Color::Black, &sfFont, 99, 1, 1, 1,				     iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Beschleungigt das\n Traning, bei\ngleicher Effektivit�t,\num 5%\nKosten: 100"										 													, 350, sf::Color::Black, &sfFont, 99, 1, 1, 2, 1 * iBreite + 2 * iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Verbessert die Traningsmethoden wodurch die Effektivit�t ansteigt die Einheit wird noch starker und erhalt mehr erfahrung\nKosten: 100"									, 350, sf::Color::Black, &sfFont, 99, 1, 1, 3, 2 * iBreite + 3 * iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Reduzierung der Traningskosten\nKosten: 100"														 																	, 350, sf::Color::Black, &sfFont, 99, 1, 1, 3, 3 * iBreite + 4 * iAbstandthalter + 15, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),

	};

	
};

