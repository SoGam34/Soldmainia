#pragma once
#include "Animationen.h"

class Data
{
public:
	Data()    
	{

		WindowSize.x = 1020;
		WindowSize.y = 500;

		sfFont.loadFromFile("Texturen/ArialCEMTBlack.ttf");

		cAnimationen.setFont(&sfFont);
		//BAZ
		aKacheln[11].ButtonHinzufuegen(3 * iAbstandthalter + 3 * iBreite + 35, 2 * iHohe + 50, 200, 30, 4, "Upgrade", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255,150,0), sf::Color::White, aKacheln[11].getGroese().x, aKacheln[11].getGroese().y);
		aKacheln[10].ButtonHinzufuegen(2 * iAbstandthalter + 2 * iBreite + 35, 2 * iHohe + 50, 200, 30, 3, "Upgrade", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255,150,0), sf::Color::White, aKacheln[10].getGroese().x, aKacheln[10].getGroese().y);
		aKacheln[9].ButtonHinzufuegen(1 * iAbstandthalter + 1 * iBreite  + 35, 2 * iHohe + 50, 200, 30, 2, "Upgrade", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255,150,0), sf::Color::White, aKacheln[9]. getGroese().x, aKacheln[9].getGroese().y);
		aKacheln[8].ButtonHinzufuegen(15 + iAbstandthalter,					  2 * iHohe + 50, 200, 30, 1, "Starten",				sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255,150,0), sf::Color::White, aKacheln[8].getGroese().x, aKacheln[8].getGroese().y);
		aKacheln[8].ButtonHinzufuegen(35,												     350,	200, 30, 11, "Mehr Mitglieder",		sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255,150,0), sf::Color::White, aKacheln[8].getGroese().x, aKacheln[8].getGroese().y);
		aKacheln[8].ButtonHinzufuegen(35,													 400,	200, 30, 12, "Weniger Mitglieder",	sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255,150,0), sf::Color::White, aKacheln[8].getGroese().x, aKacheln[8].getGroese().y);

		//Scoutbuero
		aKacheln[12].ButtonHinzufuegen(									   35, 450 , 200, 30, 1, "Starten", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255,150,0), sf::Color::White, aKacheln[12].getGroese().x, aKacheln[12].getGroese().y);
		aKacheln[13].ButtonHinzufuegen(1 * iAbstandthalter + 1 * iBreite + 35, 450, 200, 30, 2, "Upgrade", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, aKacheln[13].getGroese().x, aKacheln[13].getGroese().y);
		aKacheln[14].ButtonHinzufuegen(2 * iAbstandthalter + 2 * iBreite + 35, 450, 200, 30, 3, "Upgrade", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, aKacheln[14].getGroese().x, aKacheln[14].getGroese().y);
		aKacheln[15].ButtonHinzufuegen(3 * iAbstandthalter + 3 * iBreite + 35, 450, 200, 30, 4, "Upgrade", sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, aKacheln[15].getGroese().x, aKacheln[15].getGroese().y);
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

	int getBekanntheit()
	{
		return iBekanntheit;
	}

	void setBekanntheit(int value)
	{
		iBekanntheit = value;
	}

	int getBatilionsgroese()
	{
		return iBatilonsgroese;
	}

	void setBatilionsgroese(int value)
	{
		iBatilonsgroese = value;
	}

	float getBatilionGeschwindikeitsfaktor()
	{
		return iGeschwindikeitsFaktor[0];
	}

	void setBatilionGeschwindikeitsFaktor(float value)
	{
		iGeschwindikeitsFaktor[0] = value;
	}

	float getScoutbueroGeschwindikeitsfaktor()
	{
		return iGeschwindikeitsFaktor[1];
	}

	void setScoutbueroGeschwindikeitsFaktor(float value)
	{
		iGeschwindikeitsFaktor[1] = value;
	}

	float getGrundstaerke()
	{
		return fGrundstaerke;
	}

	void setGrundstaerke(int starke)
	{
		fGrundstaerke = starke;
	}

	int getKostenProKopf()
	{
		return iKostenproKopf;
	}

	void setKostenProKopf(int kosten)
	{
		iKostenproKopf = kosten;
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

	int getfUpgradeKosten(int Reihe, int Spalte)
	{
		return fUpgradeKosten[Reihe][Spalte];
	}

	void setBenarichtigungAktiv()
	{
		bBenarichtigungAktiv = true;
	}

	bool getBenarichtigungAktiv()
	{
		return bBenarichtigungAktiv;
	}

	void setfUpgradeKosten(int Reihe, int Spalte, float neueKosten)
	{
		fUpgradeKosten[Reihe][Spalte] = neueKosten;
	}

	int getBreite()
	{
		return iBreite;
	}

	void setBreite(int value)
	{
		iBreite = value;
	}

	int getHohe()
	{
		return iHohe;
	}

	void setHohe(int value)
	{
		iHohe = value;
	}

	void getUpgradeFaktorScoutbuero(int Spalte, int Reihe, float value)
	{
		UpgradeFaktorScoutbuero[Spalte][Reihe] = value;
	}

	float getUpgradeFaktorScoutbuero(int Spalte, int Reihe)
	{
		return UpgradeFaktorScoutbuero[Spalte][Reihe];
	}

	sf::Vector2f getWindowSize()
	{
		return WindowSize;
	}

	void setWindowSize(sf::Vector2f windowsize)
	{
		WindowSize = windowsize;
	}

private:

	sf::Vector2f WindowSize;

	//Kachel
	int iBreite = 230;
	int iHohe = 200;
	int iAbstandthalter = 20;
	sf::Font sfFont;

	//BAZ
	int iBekanntheit = 1;
	int iBatilonsgroese = 10;
	int iKostenproKopf = 70;
	float iGeschwindikeitsFaktor[2]{ 1,1 };//BaZ, Scout 
	float fGrundstaerke = 10;

	// Animationen
	Animationen cAnimationen;
	bool bBenarichtigungAktiv = false;

	//Geld
	int iKontostand = 1000000000;
	float fUpgradeKosten[2][3]
	{
		100,100,1000, //BAZ
		100,1000,100	 //Scoutb�ro
	};

	float UpgradeFaktorScoutbuero[3][3]
	{
		//Geschwindikeit, Kosten Reduzieren 
		2.5, 1.4, 1.2,
		//Rang Scoutb�ro
		2,   36,  45,
		//Grundstarke Batilion
		2.5, 2,2
	};
	
	bool bUpgradeAnimation = false;

	Kachel aKacheln[16]
	{
		//Erste Reihe beginnt bei 70
		// Hauptmenu
		//					Text					PosTextX				PosTextY
		Kachel("Zentrale"					, 260, sf::Color::Black, sfFont, 15,					iAbstandthalter+15, 70, 1,					 iAbstandthalter, 70, iBreite, iHohe, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Batilionausbildungszentrum" , 260, sf::Color::Black, sfFont, 8 , 1 * iBreite + 2 * iAbstandthalter+15, 70, 2, 1 * iBreite + 2 * iAbstandthalter, 70, iBreite, iHohe, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Tr�ningszentrum"			, 260, sf::Color::Black, sfFont, 11, 2 * iBreite + 3 * iAbstandthalter+15, 70, 3, 2 * iBreite + 3 * iAbstandthalter, 70, iBreite, iHohe, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Scout Buero"					, 260, sf::Color::Black, sfFont, 10, 3 * iBreite + 4 * iAbstandthalter+15, 70, 4, 3 * iBreite + 4 * iAbstandthalter, 70, iBreite, iHohe, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		//zweite Reihe						  
		Kachel("Auftrage"					, 280 + iHohe , sf::Color::Black, sfFont, 3, 1 * iBreite + 2 * iAbstandthalter + 15, 70 + 1 * iAbstandthalter + iHohe, 6, 1 * iBreite + 2 * iAbstandthalter, 70 + 1 * iAbstandthalter + iHohe, iBreite, iHohe, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Aktive Auftrage"			, 280 + iHohe , sf::Color::Black, sfFont, 2, 2 * iBreite + 3 * iAbstandthalter + 15, 70 + 1 * iAbstandthalter + iHohe, 7, 2 * iBreite + 3 * iAbstandthalter, 70 + 1 * iAbstandthalter + iHohe, iBreite, iHohe, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Logistik System"			, 280 + iHohe , sf::Color::Black, sfFont, 9, 3 * iBreite + 4 * iAbstandthalter + 15, 70 + 1 * iAbstandthalter + iHohe, 8, 3 * iBreite + 4 * iAbstandthalter, 70 + 1 * iAbstandthalter + iHohe, iBreite, iHohe, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Erholungsresort"			, 280 + iHohe , sf::Color::Black, sfFont, 7, iAbstandthalter + 15					, 70 + 1 * iAbstandthalter + iHohe, 5, 					 iAbstandthalter, 70 + 1 * iAbstandthalter + iHohe, iBreite, iHohe, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),

		//BAZ
		Kachel("Neues Batilion Ausbilden\nGr��e: 10\nKampfkraft: 1000" , 200, sf::Color::Black, sfFont, 99,	1*iAbstandthalter				, 95, 9 ,					 iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Beschleunigt die\nAusbildungsdauer um 5%\n Kosten 100" , 350, sf::Color::Black, sfFont,  4, 1 * iBreite + 2 * iAbstandthalter+15, 95, 10, 1 * iBreite + 2 * iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Erhoung der Grundst�rke\nKosten 100"				   , 350, sf::Color::Black, sfFont,  6, 2 * iBreite + 3 * iAbstandthalter+15, 95, 11, 2 * iBreite + 3 * iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Reduzierung der Kosten\nKosten 100"	   				   , 350, sf::Color::Black, sfFont, 14, 3 * iBreite + 4 * iAbstandthalter+15, 95, 12, 3 * iBreite + 4 * iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
	
		//Scoutb�ro
		Kachel("Einselk�mpfer Rekutieren\n(EM)\nEin EM bekommt\nein Teil der Finanzellen\nBehlohnung und hat\neine Affinit�t.\nDie Affinit�t erlaubt\ndie Ausstatung spezieller\nWaffen und bringt\nVorteile bei bestimmten\nAuftragen.", 160, sf::Color::Black, sfFont, 99, iAbstandthalter,					95, 13,					    iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Beschleungigt die\nSuche um 5%\nKosten: 100"										 																																	, 350, sf::Color::Black, sfFont, 4, 1 * iBreite + 2 * iAbstandthalter+15, 95, 14, 1 * iBreite + 2 * iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Das Scoutb�ro\nfindet Einselkampfer die\neinen hohren Rang\nund Potenzial habne\nKosten: 100"														 																	, 350, sf::Color::Black, sfFont, 5, 2 * iBreite + 3 * iAbstandthalter+15, 95, 15, 2 * iBreite + 3 * iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
		Kachel("Reduzierung der Kosten\nKosten: 100"														 																															, 350, sf::Color::Black, sfFont, 14,3 * iBreite + 4 * iAbstandthalter+15, 95, 16, 3 * iBreite + 4 * iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color(200, 200, 200), sf::Color(100, 100, 200), sf::Color::Green),
	};
};

