#pragma once
#include "Kachel.h"
#include "Animationen.h"

class Data
{
public:
	Data() 
	{
		sfFont.loadFromFile("Texturen/ArialCEMTBlack.ttf");

		cAnimationen.setFont(&sfFont);
		//BAZ
		aKacheln[11].addButten(3 * iAbstandthalter + 3 * iBreite + 35, 2 * iHohe + 50, 200, 30, 4, "Upgrade", &sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255,150,0), sf::Color::White, aKacheln[11].getSize().x, aKacheln[11].getSize().y);
		aKacheln[10].addButten(2 * iAbstandthalter + 2 * iBreite + 35, 2 * iHohe + 50, 200, 30, 3, "Upgrade", &sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255,150,0), sf::Color::White, aKacheln[10].getSize().x, aKacheln[10].getSize().y);
		aKacheln[9].addButten(1 * iAbstandthalter + 1 * iBreite  + 35, 2 * iHohe + 50, 200, 30, 2, "Upgrade", &sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255,150,0), sf::Color::White, aKacheln[9].getSize().x, aKacheln[9].getSize().y);
		aKacheln[8].addButten(15 + iAbstandthalter, 2 * iHohe + 50, 200, 30, 1, "Starten",				&sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255,150,0), sf::Color::White, aKacheln[8].getSize().x, aKacheln[8].getSize().y);
		aKacheln[8].addButten(35,					350,			200, 30, 11, "Mehr Mitglieder",		&sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255,150,0), sf::Color::White, aKacheln[8].getSize().x, aKacheln[8].getSize().y);
		aKacheln[8].addButten(35,					400,			200, 30, 12, "Weniger Mitglieder",	&sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255,150,0), sf::Color::White, aKacheln[8].getSize().x, aKacheln[8].getSize().y);

		//Scoutbüro
		aKacheln[12].addButten(									   35, 450 , 200, 30, 1, "Starten", &sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255,150,0), sf::Color::White, aKacheln[12].getSize().x, aKacheln[12].getSize().y);
		aKacheln[13].addButten(1 * iAbstandthalter + 1 * iBreite + 35, 450 , 200, 30, 2, "Upgrade", &sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255,150,0), sf::Color::White, aKacheln[13].getSize().x, aKacheln[13].getSize().y);
		aKacheln[14].addButten(2 * iAbstandthalter + 2 * iBreite + 35, 450 , 200, 30, 3, "Upgrade", &sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255,150,0), sf::Color::White, aKacheln[14].getSize().x, aKacheln[14].getSize().y);
		aKacheln[15].addButten(3 * iAbstandthalter + 3 * iBreite + 35, 450 , 200, 30, 4, "Upgrade", &sfFont, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255,150,0), sf::Color::White, aKacheln[15].getSize().x, aKacheln[15].getSize().y);
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

	int getBatilionsgröße()
	{
		return iBatilonsgröße;
	}

	void setBatilionsgröße(int value)
	{
		iBatilonsgröße = value;
	}

	float getBatilionGeschwindikeitsfaktor()
	{
		return iGeschwindikeitsFaktor[0];
	}

	void setBatilionGeschwindikeitsFaktor(float value)
	{
		iGeschwindikeitsFaktor[0] = value;
	}

	float getScoutbüroGeschwindikeitsfaktor()
	{
		return iGeschwindikeitsFaktor[1];
	}

	void setScoutbüroGeschwindikeitsFaktor(float value)
	{
		iGeschwindikeitsFaktor[1] = value;
	}

	float getGrundstärke()
	{
		return fGrundstärke;
	}

	void setGrundstärke(int starke)
	{
		fGrundstärke = starke;
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

	void setAbstand(int value)
	{
		iAbstandthalter = value;
	}

	int getiAbstandshalter()
	{
		return iAbstandthalter;
	}

private:

	//Kachel
	int iBreite = 230;
	int iHohe = 200;
	int iAbstandthalter = 20;
	sf::Font sfFont;

	//BAZ
	int iBekanntheit = 1;
	int iBatilonsgröße = 10;
	int iKostenproKopf = 70;
	float iGeschwindikeitsFaktor[2]{ 1,1 };//BaZ, Scout 
	float fGrundstärke = 10;

	// Animationen
	Animationen cAnimationen;
	bool bBenarichtigungAktiv = false;

	//Geld
	int iKontostand = 1000000;
	float fUpgradeKosten[2][3]
	{
		100,100,100, //BAZ
		100,100,100	 //Scoutbüro
	};
	
	bool bUpgradeAnimation = false;

	Kachel aKacheln[16]
	{
		//Erste Reihe beginnt bei 70
		// Hauptmenu
		//					Text					PosTextX				PosTextY
		Kachel("Zentrale"					, 160, sf::Color::Black, &sfFont, 15,					iAbstandthalter+15, 70, 1,					 iAbstandthalter, 70, iBreite, iHohe, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Batilionausbildungszentrum" , 160, sf::Color::Black, &sfFont, 8 , 1 * iBreite + 2 * iAbstandthalter+15, 70, 2, 1 * iBreite + 2 * iAbstandthalter, 70, iBreite, iHohe, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Träningszentrum"			, 160, sf::Color::Black, &sfFont, 11, 2 * iBreite + 3 * iAbstandthalter+15, 70, 3, 2 * iBreite + 3 * iAbstandthalter, 70, iBreite, iHohe, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Scout Büro"					, 160, sf::Color::Black, &sfFont, 10, 3 * iBreite + 4 * iAbstandthalter+15, 70, 4, 3 * iBreite + 4 * iAbstandthalter, 70, iBreite, iHohe, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		//zweite Reihe						  
		Kachel("Aufträge"					, 180 + iHohe , sf::Color::Black, &sfFont, 3, 1 * iBreite + 2 * iAbstandthalter + 15, 70 + 1 * iAbstandthalter + iHohe, 6, 1 * iBreite + 2 * iAbstandthalter, 70 + 1 * iAbstandthalter + iHohe, iBreite, iHohe, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Aktive Aufträge"			, 180 + iHohe , sf::Color::Black, &sfFont, 2, 2 * iBreite + 3 * iAbstandthalter + 15, 70 + 1 * iAbstandthalter + iHohe, 7, 2 * iBreite + 3 * iAbstandthalter, 70 + 1 * iAbstandthalter + iHohe, iBreite, iHohe, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Logistik System"			, 180 + iHohe , sf::Color::Black, &sfFont, 9, 3 * iBreite + 4 * iAbstandthalter + 15, 70 + 1 * iAbstandthalter + iHohe, 8, 3 * iBreite + 4 * iAbstandthalter, 70 + 1 * iAbstandthalter + iHohe, iBreite, iHohe, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Erholungsresort"			, 180 + iHohe , sf::Color::Black, &sfFont, 7, iAbstandthalter + 15					, 70 + 1 * iAbstandthalter + iHohe, 5, 					 iAbstandthalter, 70 + 1 * iAbstandthalter + iHohe, iBreite, iHohe, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),

		//BAZ
		Kachel("Neues Batilion Ausbilden\nGröße: 10\nKampfkraft: 1000" , 200, sf::Color::Black, &sfFont, 99,	1*iAbstandthalter				, 95, 9 ,					 iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Beschleunigt die\nAusbildungsdauer um 5%\n Kosten 100" , 350, sf::Color::Black, &sfFont,  4, 1 * iBreite + 2 * iAbstandthalter+15, 95, 10, 1 * iBreite + 2 * iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Erhoung der Grundstärke\nKosten 100"				   , 350, sf::Color::Black, &sfFont,  6, 2 * iBreite + 3 * iAbstandthalter+15, 95, 11, 2 * iBreite + 3 * iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Reduzierung der Kosten\nKosten 100"	   				   , 350, sf::Color::Black, &sfFont, 14, 3 * iBreite + 4 * iAbstandthalter+15, 95, 12, 3 * iBreite + 4 * iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
	
		//Scoutbüro
		Kachel("Einselkämpfer Rekutieren\n(EM)\nEin EM bekommt\nein Teil der Finanzellen\nBehlohnung und hat\neine Affinität.\nDie Affinität erlaubt\ndie Ausstatung spezieller\nWaffen und bringt\nVorteile bei bestimmten\nAuftragen.", 160, sf::Color::Black, &sfFont, 99, iAbstandthalter,					95, 1,					 iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Beschleungigt die\nSuche um 5%\nKosten: 100"										 																																	, 350, sf::Color::Black, &sfFont, 4, 1 * iBreite + 2 * iAbstandthalter+15, 95, 2, 1 * iBreite + 2 * iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Das Scoutbüro\nfindet Einselkampfer die\neinen hohren Rang\nund Potenzial habne\nKosten: 100"														 																	, 350, sf::Color::Black, &sfFont, 5, 2 * iBreite + 3 * iAbstandthalter+15, 95, 3, 2 * iBreite + 3 * iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
		Kachel("Reduzierung der Kosten\nKosten: 100"														 																															, 350, sf::Color::Black, &sfFont, 14,3 * iBreite + 4 * iAbstandthalter+15, 95, 3, 3 * iBreite + 4 * iAbstandthalter, 70, iBreite, 2 * iHohe + iAbstandthalter, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green),
	};
};

