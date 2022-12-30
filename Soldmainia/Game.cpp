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

	TextAnzeigeinitzaliesieren();
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
	while (cView->getWindow().isOpen())
	{
		update();
		mahlen();
		checkSortcuts();
	}
}

void Game::TextAnzeigeinitzaliesieren()
{
	//Hauptmenu erste Zeile
	myData->getKacheln(0).changeText("Zentrale", 250);
	myData->getKacheln(1).changeText("Batilionausbildungszentrum", 250);
	myData->getKacheln(2).changeText("Traningszentrum", 250);
	myData->getKacheln(3).changeText("Scout B�ro", 250);
	//Hauptmenu zweite Zeile
	myData->getKacheln(4).changeText("Auftr�ge", 255 + 220);
	myData->getKacheln(5).changeText("Aktive Auftr�ge", 255 + 220);
	myData->getKacheln(6).changeText("Logistik System", 255 + 220);
	myData->getKacheln(7).changeText("Erholungsresort", 255 + 220);
	//BAZ
	myData->getKacheln(9).changeText("Beschleunigt die\nAusbildungsdauer um 5%\n Kosten 100", 350);
	myData->getKacheln(10).changeText("Erhoung der Grundst�rke\nKosten 100", 350);
	myData->getKacheln(11).changeText("Reduzierung der Kosten\nKosten 100", 350);
	//Scoutb�ro
	myData->getKacheln(12).changeText("Einselk�mpfer Rekutieren\n(EM)\nEin EM bekommt\nein Teil der Finanzellen\nBehlohnung und hat\neine Affinit�t.\nDie Affinit�t erlaubt\ndie Ausstatung spezieller\nWaffen und bringt\nVorteile bei bestimmten\nAuftragen.", 200);
	myData->getKacheln(13).changeText("Beschleungigt die\nSuche um 5%\nKosten: 100", 350);
	myData->getKacheln(14).changeText("Das Scoutb�ro\nfindet Einselkampfer die\neinen hohren Rang\nund Potenzial habne\nKosten: 100", 320);
	myData->getKacheln(15).changeText("Reduzierung der Kosten\nKosten: 100", 350);
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
		case 5:
		{
			cBAZ->EndeAusbildung();
		}
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
		myData->getKacheln(i).update();
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

void Game::checkSortcuts()
{
	while (cView->getWindow().pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{

			cView->getWindow().close();
		}

		else if (event.type == sf::Event::Resized)
		{
			sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
			cView->getWindow().setView(sf::View(visibleArea));

			cView->ReSize();
		}

		else if (event.type == sf::Event::TextEntered)
		{
			if (myData->getKacheln(8).getTextfeldAusgewahltZustand()||myData->getKacheln(8).EnterPress(event))
				myData->getKacheln(8).updateTextfelder(event, sf::Mouse::getPosition(cView->getWindow()));

			else
			{
				if (cKeyboard.isKeyPressed(cKeyboard.Escape))
					cView->getWindow().close();

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
	}
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
		cView->DrawNichtVerf�gbar();
	}break;
	}
}
