#include "Game.h"

Game::Game()
{
	myData = new Data();

	//Gebaude
	cBAZ = new Batilion_Ausbildungszentrum(myData);
	cBAZ->aktstd();

	cScoutbuero = new Scoutbuero(myData);
	
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
	delete cScoutbuero;
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
	myData->getKacheln(3).changeText("Scout Buero", 250);
	//Hauptmenu zweite Zeile
	myData->getKacheln(4).changeText("Auftraege", 255 + 220);
	myData->getKacheln(5).changeText("Aktive Auftraege", 255 + 220);
	myData->getKacheln(6).changeText("Logistik System", 255 + 220);
	myData->getKacheln(7).changeText("Erholungsresort", 255 + 220);
	//BAZ
	myData->getKacheln(9).changeText("Beschleunigt die\nAusbildungsdauer um 5%\n Kosten 100", 350);
	myData->getKacheln(10).changeText("Erhoung der Grundstaerke\nKosten 100", 350);
	myData->getKacheln(11).changeText("Reduzierung der Kosten\nKosten 100", 350);
	//Scoutbuero
	myData->getKacheln(12).changeText("Einselkaempfer Rekutieren\n(EM)\nEin EM bekommt\nein Teil der Finanzellen\nBehlohnung und hat\neine Affinitaet.\nDie Affinitaet erlaubt\ndie Ausstatung spezieller\nWaffen und bringt\nVorteile bei bestimmten\nAuftragen.", 200);
	myData->getKacheln(13).changeText("Beschleungigt die\nSuche um 5%\nKosten: 100", 350);
	myData->getKacheln(14).changeText("Das Scoutbuero\nfindet Einselkampfer die\neinen hohren Rang\nund Potenzial habne\nKosten: 100", 320);
	myData->getKacheln(15).changeText("Reduzierung der Kosten\nKosten: 100", 350);
}

void Game::update()
{
	vMauspos = cView->getMousPos();

	switch (eAktuellesMenu)
	{
	case Hauptmenu:
	{
		int temp = 0;
		for (int i = 0; i < 8; i++)
		{
			//Kacheln ueberpruefen
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
						eAktuellesMenu = Traeningszentrum;
					}break;
					case 4: {
						eAktuellesMenu = scoutbuero;
					}break;
					case 5: {
						eAktuellesMenu = Erholungsresort;
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
					myData->getHauptmenu(i).setTexturePosition(sf::Vector2f(i * myData->getBreite() + (i + 1) * 20 + 15, 70));

				else
				{
					myData->getHauptmenu(i).setTexturePosition(sf::Vector2f(temp * myData->getBreite() + (temp + 1) * 20 + 15, myData->getHohe()+90));
				}
			}

			if (i > 3)
				temp++;
		}
	}break;
	
	case Zentrale:
	{
		//for (int i = 0; i < 8; i++)
		//{
		//	//Kacheln ueberpruefen
		//	if (myData.get[i]->ishover(vMauspos))
		//	{
		//		vKacheln[i]->sethoverColor();
		//		//Butten ueberpruefen
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
		switch ((myData->getAnimationen().getKeineBenarichtigung())?99: updateButtons(8, 4))	// Bestimmen welcher Butten gedrueckt wurde 
		{
		case 1: 
		{
			cBAZ->startAusbildung();	//starten Gedruekt
		}break;
		case 11: 
		{
			cBAZ->AnzahlErhohen();		//Anzahl Mitglieder wird erhoeht
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
			cBAZ->UpgradeGrundstarke();	 //Upgrade Grundstaerke
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

	case scoutbuero:
	{
		switch ((myData->getAnimationen().getKeineBenarichtigung()) ? 99 : updateButtons(12, 4))
		{
		case 1:
		{
			cScoutbuero->startSuche();				// Suche Starten
		}break;
		case 2:
		{
			cScoutbuero->UpgradeGeschwindikeit();	// Beschleunigt die Suche 
		}break;
		case 3:
		{
			cScoutbuero->UpgradeRang();				// Erhoeht den mindest Rang
		}break;
		case 4:
		{
			cScoutbuero->UpgradeKosten();			// Reduzierung der Suchkosten
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
	default:
	{

	}break;

	}

	if (clTagesTimer.getElapsedTime().asSeconds() >= 1.5)
	{
		neuerTag();
		clTagesTimer.restart();
	}
	
	myData->getAnimationen().Aktualisieren(vMauspos);

}

int Game::updateButtons(int iOffset, int iAnzahlKacheln)
{
	int iButtenID = 99;
	bool bButtenGedrueckt = false;

	for (int i = iOffset; i < iAnzahlKacheln+iOffset; i++)
	{
		myData->getKacheln(i).update();
		//Kacheln ueberpruefen
		if (myData->getKacheln(i).ishover(vMauspos))
		{
			myData->getKacheln(i).sethoverColor();
			//Butten ueberpruefen
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
					eAktuellesMenu = scoutbuero;
			}
		}
	}
}

void Game::neuerTag()
{
	iTag++;
	cBAZ->updateTimer();
	cScoutbuero->updateTimer();
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
	default: {
		cView->DrawNichtVerfuegbar();
	}break;
	}
}
