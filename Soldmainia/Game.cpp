#include "Game.h"

Game::Game()
{
	myData = new Data();

	//Gebaude
	cBAZ = new Batilion_Ausbildungszentrum(myData);
	cBAZ->aktualisierenInformationsText();

	cScoutbuero = new Scoutbuero(myData);

	cTraingzentrum = new Traningszentrum(myData);

	cZentrale = new Zentale(myData);

	cErholungsresort = new Erholungsresort(myData);

	cView = new View(myData);
	iTag = 0;
	bAuswahl = false;
	TextAnzeigeinitzaliesieren();
}

Game::~Game()
{
	delete cBAZ;
	delete cScoutbuero;
	delete cTraingzentrum;
	delete cZentrale;
	delete cErholungsresort;
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
	myData->getKacheln(3).changeText("Scout B�ro", 160);
	//Hauptmenu zweite Zeile
	myData->getKacheln(4).changeText("Auftr�ge", 160 + 220);
	myData->getKacheln(5).changeText("Aktive Auftr�ge", 160 + 220);
	myData->getKacheln(6).changeText("Logistik System", 160 + 220);
	myData->getKacheln(7).changeText("Erholungsresort", 160 + 220);
	//BAZ
	myData->getKacheln(9).changeText("Beschleunigt die\nAusbildungsdauer um 5%\n Kosten 100", 350);
	myData->getKacheln(10).changeText("Erhoung der Grundst�rke\nKosten 100", 350);
	myData->getKacheln(11).changeText("Reduzierung der Kosten\nKosten 100", 350);
	//Scoutb�ro
	myData->getKacheln(12).changeText("Einselk�mpfer Rekutieren\n(EM)\nEin EM bekommt\nein Teil der Finanzellen\nBehlohnung und hat\neine Affinit�t.\nDie Affinit�t erlaubt\ndie Ausstatung spezieller\nWaffen und bringt\nVorteile bei bestimmten\nAuftragen.", 200);
	myData->getKacheln(13).changeText("Beschleungigt die\nSuche um 5%\nKosten: 100", 350);
	myData->getKacheln(14).changeText("Das Scoutb�ro\nfindet Einselkampfer die\neinen hohren Rang\nund Potenzial habne\nKosten: 100", 320);
	myData->getKacheln(15).changeText("Reduzierung der Kosten\nKosten: 100", 350);
	//Traningzentrum
	myData->getKacheln(16).changeText("Sie wahlen eine\nEinheit(Batilion/EM) aus,\nwelche im Zentrum\ntraniert wird,\ndadurch wird sie\nStarker und erhalt\nKampferfahrung was ein\nVorteil in Einsatzen\nist.", 160);
	myData->getKacheln(17).changeText("Beschleungigt das\n Traning, bei\ngleicher Effektivit�t,\num 5%\nKosten: 100", 290);
	myData->getKacheln(18).changeText("Verbessert die\nTraningsmethoden\nwodurch die Effektivit�t\nansteigt die Einheit\nwird noch starker\nund erhalt mehr\nerfahrung\nKosten: 100", 300);
	myData->getKacheln(19).changeText("Reduzierung der\nTraningskosten\nKosten: 100", 300);
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
			//Kacheln �berpr�fen
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
						eAktuellesMenu = scoutbuero;
					}break;
					case 5: {
						eAktuellesMenu = erholungsresort;
					}break;
					case 6: {
						eAktuellesMenu = Auftraege;
					}break;
					case 7: {
						eAktuellesMenu = AAuftraege;
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
			cBAZ->BeginnAufgabe();	//starten Gedr�kt
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
			cBAZ->BeschleunigungDerAufgabenDurchfuehrung();	//Upgrade Geschwindikeit
		}break;
		case 3:
		{
			cBAZ->ErhohenDerGrundstarke();	 //Upgrade Grundst�rke
		}break;
		case 4: 
		{
			cBAZ->ReduzierenDerAusfuhrungsKosten();		//Upgrade zur kosten Reduzierung
		}break;
		case 5:
		{
			cBAZ->Vorbereiten_neueAusbildung();
		}
		}
	}break;

	case scoutbuero:
	{
		switch (updateButtons(12, 4))
		{
		case 1:
		{
			cScoutbuero->BeginnAufgabe();				// Suche Starten
		}break;
		case 2:
		{
			cScoutbuero->BeschleunigungDerAufgabenDurchfuehrung();	// Beschleunigt die Suche 
		}break;
		case 3:
		{
			cScoutbuero->ErhohenDesMoeglichenRanges();				// Erh�ht den mindest Rang
		}break;
		case 4:
		{
			cScoutbuero->ReduzierenDerAusfuhrungsKosten();			// Reduzierung der Suchkosten
		}break;
		case 5:
		{
			cScoutbuero->Annehmen();					// Annehmen 
		}break;
		case 6:
		{
			cScoutbuero->Ablehnen();					// Ablehnen 
		}break; 
		}
	}break;

	case traningszentrum:
	{
		if (bAuswahl)
		{
			auto temp = cTraingzentrum->updateAuswahl(vMauspos);
			if (temp.has_value())
			{
				cTraingzentrum->AuswahlZuOrdnen(temp.value());
				bAuswahl = false;
			}
		}

		else
		{
			switch (updateButtons(16, 4))
			{
			case 2:
			{
				cTraingzentrum->BeschleunigungDerAufgabenDurchfuehrung();
			}break;
			case 3:
			{
				cTraingzentrum->ErhohenDerTraningsWirksamkeit();
			}break;
			case 4:
			{
				cTraingzentrum->ReduzierenDerAusfuhrungsKosten();
			}break;
			case 5:
			{
				cTraingzentrum->LangeTrainingsDauer();
				bAuswahl = true;
			}break;
			case 6:
			{
				cTraingzentrum->KurzeTraningsDauer();
				bAuswahl = true;
			}break;
			case 7:
			{
				cTraingzentrum->MittlereTrainingsDauer();
				bAuswahl = true;
			}break;
			}
		}
	}break;

	case erholungsresort:
	{
		if (bAuswahl)
		{
			auto temp = cErholungsresort->updateAuswahl(vMauspos);
			if (temp.has_value())
			{
				cErholungsresort->AuswahlZuOrdnen(temp.value());
				bAuswahl = false;
			}
		}

		else
		{
			switch (updateButtons(24, 4))
			{
			case 2:
			{
				cErholungsresort->BeschleunigungDerAufgabenDurchfuehrung();
			}break;
			case 3:
			{
				cErholungsresort->ErhohenDerTraningsWirksamkeit();
			}break;
			case 4:
			{
				cErholungsresort->ReduzierenDerAusfuhrungsKosten();
			}break;

			case 5:
				cErholungsresort->leeren();
				cErholungsresort->SucheNachEinsetzbarenEinheiten();
				bAuswahl = true;
			}
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
	bool bButtenGedrueckt = false;

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
					bButtenGedrueckt = true;
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
	return bButtenGedrueckt ? iButtenID : 99;
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
		eAktuellesMenu = scoutbuero;
}

void Game::neuerTag()
{
	iTag++;

	cBAZ->aktualisierenTimer();
	cScoutbuero->aktualisierenTimer();
	cTraingzentrum->aktualisierenTimer();
	cErholungsresort->aktualisierenTimer();

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
	case scoutbuero:
	{
		cView->DrawScoutbuero(iTag);
	}break;
	case traningszentrum:
	{
		if (!bAuswahl)
			cView->DrawTraningszentrum(iTag);
		else
			cView->DrawDiffrent(*cTraingzentrum);
	}break;
	case erholungsresort:
	{
		if (!bAuswahl)
			cView->DrawErholungsresort(iTag);
		else
			cView->DrawDiffrent(*cErholungsresort);
	}break;
	default: {

	}break;
	}
}
