#include "PreHeader.h"
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
	myData->getKacheln(0).TextAendern("Zentrale", 250);
	myData->getKacheln(1).TextAendern("Batilionausbildungszentrum", 250);
	myData->getKacheln(2).TextAendern("Traningszentrum", 250);
	myData->getKacheln(3).TextAendern("Scout Buero", 250);
	//Hauptmenu zweite Zeile
	myData->getKacheln(4).TextAendern("Auftraege", 255 + 220);
	myData->getKacheln(5).TextAendern("Aktive Auftraege", 255 + 220);
	myData->getKacheln(6).TextAendern("Logistik System", 255 + 220);
	myData->getKacheln(7).TextAendern("Erholungsresort", 255 + 220);
	//BAZ
	myData->getKacheln(9) .TextAendern("Beschleunigt die\nAusbildungsdauer um 5%\n Kosten 100", 350);
	myData->getKacheln(10).TextAendern("Erhoung der Grundstaerke\nKosten 100", 350);
	myData->getKacheln(11).TextAendern("Reduzierung der Kosten\nKosten 100", 350);
	//Scoutbuero
	myData->getKacheln(12).TextAendern("Einselkaempfer Rekutieren\n(EM)\nEin EM bekommt\nein Teil der Finanzellen\nBehlohnung und hat\neine Affinitaet.\nDie Affinitaet erlaubt\ndie Ausstatung spezieller\nWaffen und bringt\nVorteile bei bestimmten\nAuftragen.", 200);
	myData->getKacheln(13).TextAendern("Beschleungigt die\nSuche um 5%\nKosten: 100", 350);
	myData->getKacheln(14).TextAendern("Das Scoutbuero\nfindet Einselkampfer die\neinen hohren Rang\nund Potenzial habne\nKosten: 100", 320);
	myData->getKacheln(15).TextAendern("Reduzierung der Kosten\nKosten: 100", 350);
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
			if (myData->getHauptmenu(i).MausSchwebtDrüber(vMauspos))
			{
				if (myData->getHauptmenu(i).getTextureGroessenSkalierungsFaktor() < 1.1)
				{
					myData->getHauptmenu(i).setTextureGroessenSkalierungsFaktor(myData->getKacheln(i).getTextureGroessenSkalierungsFaktor() + 0.01);
					myData->getHauptmenu(i).setTexturePosition(sf::Vector2f(myData->getKacheln(i).getTexturePosition().x-1, myData->getKacheln(i).getTexturePosition().y - 2));
				}

				if (myData->getHauptmenu(i).wirdGedrückt())
				{
					myData->getHauptmenu(i).setKachel_Gedrücktfarbe();
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
					myData->getHauptmenu(i).setKachel_Schwebefarbe();

			}
			else
			{
				myData->getHauptmenu(i).setTextureGroessenSkalierungsFaktor(1);
				myData->getHauptmenu(i).setKachel_Hintergrundfarbe();
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
		std::optional<int> iButtenID = {};
	bool bButtenGedrueckt = false;

	for (int i = iOffset; i < iAnzahlKacheln+iOffset; i++)
	{
		myData->getKacheln(i).aktualisieren();
		//Kacheln ueberpruefen
		if (myData->getKacheln(i).MausSchwebtDrüber(vMauspos))
		{
			myData->getKacheln(i).setKachel_Schwebefarbe();
			//Butten ueberpruefen
			 iButtenID = myData->getKacheln(i).ueberprueftAlleButtonObMausSchwebtDrüber(vMauspos);
			if (iButtenID.has_value())
				if (myData->getKacheln(i).ueberprueftButtonObGedruektWird(iButtenID.value()))
					bButtenGedrueckt = true;
				else {}
			else
				myData->getKacheln(i).setAlleButtenAufHintergrundfarbe();
		}
		else
		{
			myData->getKacheln(i).setKachel_Hintergrundfarbe();
			myData->getKacheln(i).setTextureGroessenSkalierungsFaktor(1);
		}
	}
	return bButtenGedrueckt ? iButtenID.value() : 99;
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
			if (myData->getKacheln(8).getTextfeldAusgewahltStatus()||myData->getKacheln(8).ueberpruefenObEnterGedruekt(event))
				myData->getKacheln(8).aktualisierenTextfelder(event, sf::Mouse::getPosition(cView->getWindow()));

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
