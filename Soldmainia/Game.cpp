#include "Game.h"

Game::Game()
{
	myData = new Data();

	//Gebaude
	cBAZ = new Batilion_Ausbildungszentrum(myData);
	cBAZ->aktstd();

	cScoutbüro = new Scoutbüro(myData);

	cTraingzentrum = new Traningszentrum(myData);

	cZentrale = new Zentale(myData);

	cErholungsresort = new Erholungsresort(myData);
	
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
	delete cScoutbüro;
	delete cTraingzentrum;
	delete cZentrale;
	delete cErholungsresort;
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
		checkSortcuts();
	}
}

void Game::TextAnzeigeinitzaliesieren()
{
	//Hauptmenu erste Zeile
	myData->getKacheln(0).changeText("Zentrale", 160);
	myData->getKacheln(1).changeText("Batilionausbildungszentrum", 160);
	myData->getKacheln(2).changeText("Traningszentrum", 160);
	myData->getKacheln(3).changeText("Scout Büro", 160);
	//Hauptmenu zweite Zeile
	myData->getKacheln(4).changeText("Aufträge", 160 + 220);
	myData->getKacheln(5).changeText("Aktive Aufträge", 160 + 220);
	myData->getKacheln(6).changeText("Logistik System", 160 + 220);
	myData->getKacheln(7).changeText("Erholungsresort", 160 + 220);
	//BAZ
	myData->getKacheln(9).changeText("Beschleunigt die\nAusbildungsdauer um 5%\n Kosten 100", 350);
	myData->getKacheln(10).changeText("Erhoung der Grundstärke\nKosten 100", 350);
	myData->getKacheln(11).changeText("Reduzierung der Kosten\nKosten 100", 350);
	//Scoutbüro
	myData->getKacheln(12).changeText("Einselkämpfer Rekutieren\n(EM)\nEin EM bekommt\nein Teil der Finanzellen\nBehlohnung und hat\neine Affinität.\nDie Affinität erlaubt\ndie Ausstatung spezieller\nWaffen und bringt\nVorteile bei bestimmten\nAuftragen.", 200);
	myData->getKacheln(13).changeText("Beschleungigt die\nSuche um 5%\nKosten: 100", 350);
	myData->getKacheln(14).changeText("Das Scoutbüro\nfindet Einselkampfer die\neinen hohren Rang\nund Potenzial habne\nKosten: 100", 320);
	myData->getKacheln(15).changeText("Reduzierung der Kosten\nKosten: 100", 350);
	//Traningzentrum
	myData->getKacheln(12).changeText("Sie wahlen eine\nEinheit(Batilion/EM) aus,\nwelche im Zentrum\ntraniert wird,\ndadurch wird sie\nStarker und erhalt\nKampferfahrung was ein\nVorteil in Einsatzen\nist.", 160);
	myData->getKacheln(12).changeText("Beschleungigt das\n Traning, bei\ngleicher Effektivität,\num 5%\nKosten: 100", 350);
	myData->getKacheln(12).changeText("Verbessert die Traningsmethoden wodurch die Effektivität ansteigt die Einheit wird noch starker und erhalt mehr erfahrung\nKosten: 100", 350);
	myData->getKacheln(12).changeText("Reduzierung der Traningskosten\nKosten: 100", 350);
}

void Game::update()
{
	vMauspos = cView->getMousPos();

	switch (eAktuellesMenu)
	{
	case Hauptmenu:
	{
		int temp = 1;
		for (int i = 0; i < 8; i++)
		{
			//Kacheln überprüfen
			if (myData->getHauptmenu(i).ishover(vMauspos))
			{
				if (myData->getHauptmenu(i).getScale() < 1.1)
				{
					myData->getHauptmenu(i).setScale(myData->getKacheln(i).getScale() + 0.01);
					myData->getHauptmenu(i).setTexturePosition(sf::Vector2f(myData->getKacheln(i).getTexturePosition().x-1, myData->getKacheln(i).getTexturePosition().y - 2));
				}

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
						eAktuellesMenu = traningszentrum;
					}break;
					case 4: {
						eAktuellesMenu = scoutbüro;
					}break;
					case 5: {
						eAktuellesMenu = erholungsresort;
					}break;
					case 6: {
						eAktuellesMenu = Aufträge;
					}break;
					case 7: {
						eAktuellesMenu = AAufträge;
					}break;
					case 8: {
						eAktuellesMenu = LogistikSystem;
					}break;
					}
				}
				else
					myData->getHauptmenu(i).sethoverColor();

			}
			else
			{
				myData->getHauptmenu(i).setScale(1);
				myData->getHauptmenu(i).setNormalColor();
				
				if (i < 4)
					myData->getHauptmenu(i).setTexturePosition(sf::Vector2f(i * 230 + (i + 1) * 20+15, 70));
				else
				{
					if (temp == 4)
						temp = 0;

					myData->getHauptmenu(i).setTexturePosition(sf::Vector2f(temp * 230 + (temp + 1) * 20+15, 290));
					
				}
			}
			if(i>3)
			temp++;
		}
	}break;
	
	case Zentrale:
	{
		//for (int i = 0; i < 8; i++)
		//{
		//	//Kacheln überprüfen
		//	if (myData.get[i]->ishover(vMauspos))
		//	{
		//		vKacheln[i]->sethoverColor();
		//		//Butten überprüfen
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
		switch (updateButtons(8, 4))	// Bestimmen welcher Butten gedrückt wurde 
		{
		case 1: 
		{
			cBAZ->StartProzess();	//starten Gedrükt
		}break;
		case 11: 
		{
			cBAZ->AnzahlErhohen();		//Anzahl Mitglieder wird erhöht
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
			cBAZ->UpgradeGrundstarke();	 //Upgrade Grundstärke
		}break;
		case 4: 
		{
			cBAZ->UpgradeKosten();		//Upgrade zur kosten Reduzierung
		}break;
		}
	}break;

	case scoutbüro:
	{
		switch (updateButtons(12, 4))
		{
		case 1:
		{
			cScoutbüro->StartProzess();				// Suche Starten
		}break;
		case 2:
		{
			cScoutbüro->UpgradeGeschwindikeit();	// Beschleunigt die Suche 
		}break;
		case 3:
		{
			cScoutbüro->UpgradeRang();				// Erhöht den mindest Rang
		}break;
		case 4:
		{
			cScoutbüro->UpgradeKosten();			// Reduzierung der Suchkosten
		}break;
		case 5:
		{
			cScoutbüro->Annehmen();					// Annehmen 
		}break;
		case 6:
		{
			cScoutbüro->Ablehnen();					// Ablehnen 
		}break; 
		}
	}break;

	case traningszentrum:
	{
		switch (updateButtons(16, 4))
		{
		case 1:
		{
			cTraingzentrum->AnzeigeVorbereitung();
		}break;
		case 2:
		{
			cTraingzentrum->UpgradeGeschwindikeit();
		}break;
		case 3:
		{
			cTraingzentrum->UpgradeEffizens();
		}break;
		case 4:
		{
			cTraingzentrum->UpgradeKosten();
		}break;
		}
	}break;

	case erholungsresort:
	{
		switch (updateButtons(24, 4))
		{
		case 1:
		{

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
	bool bButtenGedrückt = false;

	for (int i = iOffset; i < iAnzahlKacheln+iOffset; i++)
	{
		//Kacheln überprüfen
		if (myData->getKacheln(i).ishover(vMauspos))
		{
			myData->getKacheln(i).sethoverColor();
			//Butten überprüfen
			 iButtenID = myData->getKacheln(i).checkButtenishover(vMauspos);
			if (iButtenID != 99)
				if (myData->getKacheln(i).checkButtenisPressed(iButtenID, vMauspos))
					bButtenGedrückt = true;
				else {}
			else
				myData->getKacheln(i).setButtenColorToNormal();
		}
		else
		{
			myData->getKacheln(i).setNormalColor();
			myData->getKacheln(i).setScale(1);
		}
	}
	return bButtenGedrückt ? iButtenID : 99;
}

void Game::checkSortcuts()
{
	if (cKeyboard.isKeyPressed(cKeyboard.Escape))
		cView->Close();

	if (cKeyboard.isKeyPressed(cKeyboard.H))
		eAktuellesMenu = Hauptmenu;

	if (cKeyboard.isKeyPressed(cKeyboard.Z))
		eAktuellesMenu = Zentrale;

	if (cKeyboard.isKeyPressed(cKeyboard.A))
		eAktuellesMenu = Batilionsausbildungsstate;

	if (cKeyboard.isKeyPressed(cKeyboard.S))
		eAktuellesMenu = scoutbüro;
}

void Game::neuerTag()
{
	iTag++;
	cBAZ->updateTimer();
	cScoutbüro->updateTimer();
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
	case scoutbüro:
	{
		cView->DrawScoutbuero(iTag);
	}break;
	default: {

	}break;
	}
}
