#include "Game.h"

Game::Game()
{
	myData = new Data();

	//Gebaude
	cBAZ = new Batilion_Ausbildungszentrum(myData);
	cBAZ->aktstd();

	cScoutb�ro = new Scoutb�ro(myData);
	
	//Auswahl
	cAuswahl = new Auswahl();
	cAuswahl->setData(myData);

	cView = new View(myData);
	iTag = 0;
}

Game::~Game()
{
	delete cBAZ;
	delete cScoutb�ro;
	delete cAuswahl;
	delete cView;
	delete myData;
}

void Game::SpielLauft()
{
	while (cView->windowOpen())
	{
		update();
		mahlen();

		if (cKeyboard.isKeyPressed(cKeyboard.Escape))
			cView->Close();

		if (cKeyboard.isKeyPressed(cKeyboard.H))
			eAktuellesMenu = Hauptmenu;

		if (cKeyboard.isKeyPressed(cKeyboard.Z))
			eAktuellesMenu = Zentrale;

		if (cKeyboard.isKeyPressed(cKeyboard.A))
			eAktuellesMenu = Batilionsausbildungsstate;

		if (cKeyboard.isKeyPressed(cKeyboard.S))
			eAktuellesMenu = scoutb�ro;
	}
}

void Game::update()
{
	vMauspos = cView->getMousPos();

	switch (eAktuellesMenu)
	{
	case Hauptmenu:
	{
		for (int i = 0; i < 8; i++)
		{
			//Kacheln �berpr�fen
			if (myData->getHauptmenu(i).ishover(vMauspos))
				if (myData->getHauptmenu(i).isPressed(vMauspos))
				{
					myData->getHauptmenu(i).setPressedColor();
					switch (myData->getHauptmenu(i).getID())
					{
					case 1: {
						eAktuellesMenu = Zentrale; 
					}break;
					case 2: {
						eAktuellesMenu = Batilionsausbildungsstate;
					}break;
					case 3: {
						eAktuellesMenu = Tr�ningszentrum;
					}break;
					case 4: {
						eAktuellesMenu = scoutb�ro;
					}break;
					case 5: {
						eAktuellesMenu = Erholungsresort;
					}break;
					case 6: {
						eAktuellesMenu = Auftr�ge;
					}break;
					case 7: {
						eAktuellesMenu = AAuftr�ge;
					}break;
					case 8: {
						eAktuellesMenu = LogistikSystem;
					}break;
					}
				}
				else
					myData->getHauptmenu(i).sethoverColor();
			else
				myData->getHauptmenu(i).setNormalColor();
		}
	}break;
	
	case Zentrale:
	{
		//for (int i = 0; i < 8; i++)
		//{
		//	//Kacheln �berpr�fen
		//	if (myData.get[i]->ishover(vMauspos))
		//	{
		//		vKacheln[i]->sethoverColor();
		//		//Butten �berpr�fen
		//		int ButtonID = vKacheln[i]->checkButtenishover(vMauspos);
		//		if (ButtonID != 99)
		//			if (vKacheln[i]->checkButtenisPressed(ButtonID, vMauspos))
		//				switch (ButtonID)
		//				{
		//				case 1: {}break;
		//				}
		//	}
		//}

	}break;

	case Batilionsausbildungsstate:
	{
		switch (updateButtons(8, 4))	// Bestimmen welcher Butten gedr�ckt wurde 
		{
		case 1: 
		{
			cBAZ->startAusbildung();	//starten Gedr�kt
		}break;
		case 11: 
		{
			cBAZ->AnzahlErhohen();		//Anzahl Mitglieder wird erh�ht
		}break;
		case 12: 
		{
			cBAZ->AnzahlReduzieren();	//Anzahl der Mitglieder wird gesengt
		}break;
		case 2: 
		{
			cBAZ->UpgradeGeschwindikeit();	//Upgrade Geschwindikeit
		}break;
		case 3:
		{
			cBAZ->UpgradeGrundstarke();	 //Upgrade Grundst�rke
		}break;
		case 4: 
		{
			cBAZ->UpgradeKosten();		//Upgrade zur kosten Reduzierung
		}break;
		}
	}break;

	case scoutb�ro:
	{
		switch (updateButtons(12, 4))
		{
		case 1:
		{
			cScoutb�ro->startSuche();				// Suche Starten
		}break;
		case 2:
		{
			cScoutb�ro->UpgradeGeschwindikeit();	// Beschleunigt die Suche 
		}break;
		case 3:
		{
			cScoutb�ro->UpgradeRang();				// Erh�ht den mindest Rang
		}break;
		case 4:
		{
			cScoutb�ro->UpgradeKosten();			// Reduzierung der Suchkosten
		}break;
		case 5:
		{
			cScoutb�ro->Annehmen();					// Annehmen 
		}break;
		case 6:
		{
			cScoutb�ro->Ablehnen();					// Ablehnen 
		}break; 
		}
	}break;
	default:
	{

	}break;

	}

	if (clTagesTimer.getElapsedTime().asSeconds() >= 1.5)
	{
		neuerTag();
		clTagesTimer.restart();
	}
	
	myData->getAnimationen().Aktualisieren();

}

int Game::updateButtons(int iOffset, int iAnzahlKacheln)
{
	int iButtenID = 99;
	bool bButtenGedr�ckt = false;

	for (int i = iOffset; i < iAnzahlKacheln+iOffset; i++)
	{
		//Kacheln �berpr�fen
		if (myData->getKacheln(i).ishover(vMauspos))
		{
			myData->getKacheln(i).sethoverColor();
			//Butten �berpr�fen
			 iButtenID = myData->getKacheln(i).checkButtenishover(vMauspos);
			if (iButtenID != 99)
				if (myData->getKacheln(i).checkButtenisPressed(iButtenID, vMauspos))
					bButtenGedr�ckt = true;
				else {}
			else
				myData->getKacheln(i).setButtenColorToNormal();
		}
		else
			myData->getKacheln(i).setNormalColor();
	}
	return bButtenGedr�ckt ? iButtenID : 99;
}

void Game::neuerTag()
{
	iTag++;
	cBAZ->updateTimer();
	cScoutb�ro->updateTimer();
	if (iTag % 30 == 0)
	{
		//Sold auszahlen
	}
}

void Game::mahlen()
{
	switch (eAktuellesMenu)
	{
	case Hauptmenu: 
	{           
		cView->DrawHauptmenu(iTag);
	}break;
	case Batilionsausbildungsstate:
	{
		cView->DrawBAZ(iTag);
	}break;
	case scoutb�ro:
	{
		cView->DrawScoutbuero(iTag);
	}break;
	default: {

	}break;
	}
}
