#include "PreHeader.h"
#include "Game.h"

Game::Game()
{
	myData = std::make_shared<Data>();
	
	//Gebaude
	std::thread worker1([=]() { cBAZ = new Batilion_Ausbildungszentrum(myData, mSicherung); });
	
	std::thread worker2([=]() { cScoutbuero = new Scoutbuero(myData, mSicherung); });

	std::thread worker3([=]() { cTraingzentrum = new Traningszentrum(myData, mSicherung); });

	std::thread worker4([=]() { cZentrale = new Zentale(myData, mSicherung); });

	std::thread worker5([=]() { cErholungsresort = new Erholungsresort(myData, mSicherung); });

	std::thread worker0(&Game::TextAnzeigeinitzaliesieren, this);
	
	//Auswahl
	iTag = 0;
	bAuswahl = false;

	cView = std::make_unique<View>(myData, mSicherung);

	worker1.join();
	cBAZ->aktualisierenInformationsText();
	
	
	worker2.join();
	worker3.join();
	worker4.join();
	worker5.join();
	worker0.join();
}

Game::~Game()
{
	delete cBAZ;
	delete cScoutbuero;
	delete cTraingzentrum;
	delete cZentrale;
	delete cErholungsresort;
}

void Game::SpielLauft()
{
	while (cView->getWindow().isOpen())
	{
		update();
		
		checkSortcuts();

		Zeit();

		if (cView->getWindow().isOpen())
		{
			myData->getAnimationen().Aktualisieren(cView->getMousPos());

			mahlen();
		}
	}
}

void Game::TextAnzeigeinitzaliesieren()
{
	std::lock_guard<std::mutex> lock(mSicherung);
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
	{
		//std::lock_guard<std::mutex> lock(mSicherung);
		vMauspos = cView->getMousPos();
	}

	switch (eAktuellesMenu)
	{
		
	case Hauptmenu:
	{
		int temp = 1;
		//std::lock_guard<std::mutex> lock(mSicherung);
		for (int i = 0; i < 8; i++)
		{
			if (myData->getHauptmenu(i).MausSchwebtDrueber(vMauspos))
			{
				if (myData->getHauptmenu(i).getTextureGroessenSkalierungsFaktor() < 1.1)
				{
					myData->getHauptmenu(i).setTextureGroessenSkalierungsFaktor(myData->getKacheln(i).getTextureGroessenSkalierungsFaktor() + 0.01);
					myData->getHauptmenu(i).setTexturePosition(sf::Vector2f(myData->getKacheln(i).getTexturePosition().x-1, myData->getKacheln(i).getTexturePosition().y - 2));
				}

				if (myData->getHauptmenu(i).wirdGedruedckt())
				{
					myData->getHauptmenu(i).setKachel_Gedruecktfarbe();
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
		//std::lock_guard<std::mutex> lock(Sicherung);
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
		int temp = 0;
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			temp = (myData->getAnimationen().getKeineBenarichtigung())?99: updateButtons(8, 4);
		}
		switch (temp)	// Bestimmen welcher Butten gedr�ckt wurde 
		{
		case 1: 
		{
			cBAZ->BeginnAufgabe(mSicherung);	//starten Gedr�kt
		}break;
		case 11: 
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			cBAZ->AnzahlErhohen();		//Anzahl Mitglieder wird erh�ht
		}break;
		case 12: 
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			cBAZ->AnzahlReduzieren();	//Anzahl der Mitglieder wird gesengt
		}break;
		case 2: 
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			cBAZ->BeschleunigungDerAufgabenDurchfuehrung();	//Upgrade Geschwindikeit
		}break;
		case 3:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			cBAZ->ErhohenDerGrundstarke();	 //Upgrade Grundst�rke
		}break;
		case 4: 
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			cBAZ->ReduzierenDerAusfuhrungsKosten();		//Upgrade zur kosten Reduzierung
		}break;
		case 5:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			cBAZ->Vorbereiten_neueAusbildung();
		}break;
		}
	}break;

	case scoutbuero:
	{
		int temp = 0;
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			temp = updateButtons(12, 4);
		}
		switch (temp)
		{
		case 1:
		{
			cScoutbuero->BeginnAufgabe(mSicherung);				// Suche Starten
		}break;
		case 2:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			cScoutbuero->BeschleunigungDerAufgabenDurchfuehrung();	// Beschleunigt die Suche 
		}break;
		case 3:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			cScoutbuero->ErhohenDesMoeglichenRanges();				// Erh�ht den mindest Rang
		}break;
		case 4:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			cScoutbuero->ReduzierenDerAusfuhrungsKosten();			// Reduzierung der Suchkosten
		}break;
		case 5:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			cScoutbuero->Annehmen();					// Annehmen 
		}break;
		case 6:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
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
				cTraingzentrum->AuswahlZuOrdnen(temp.value(), mSicherung);
				bAuswahl = false;
			}
		}

		else
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
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
				cErholungsresort->AuswahlZuOrdnen(temp.value(), mSicherung);
				bAuswahl = false;
			}
		}

		else
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
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
}

int Game::updateButtons(int iOffset, int iAnzahlKacheln)
{
	std::optional<int> iButtenID = {};
	bool bButtenGedrueckt = false;

	for (int i = iOffset; i < iAnzahlKacheln+iOffset; i++)
	{
		myData->getKacheln(i).aktualisieren();
		//Kacheln ueberpruefen
		if (myData->getKacheln(i).MausSchwebtDrueber(vMauspos))
		{
			myData->getKacheln(i).setKachel_Schwebefarbe();
			//Butten ueberpruefen
			 iButtenID = myData->getKacheln(i).ueberprueftAlleButtonObMausSchwebtDrueber(vMauspos);
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
		//lockguard.~lock_guard();
	}
	return bButtenGedrueckt ? iButtenID.value() : 99;
}

void Game::checkSortcuts()
{
	sf::Event event;
	while (cView->getWindow().pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
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

void Game::Zeit()
{
	if (clTagesTimer.getElapsedTime().asSeconds() >= 1.5)
	{
		iTag++;

		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			cBAZ->aktualisierenTimer();
			cScoutbuero->aktualisierenTimer();
			cTraingzentrum->aktualisierenTimer();
			cErholungsresort->aktualisierenTimer();
		}

		if (iTag % 30 == 0)
		{
			//Sold auszahlen
		}
		clTagesTimer.restart();
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
		cView->DrawNichtVerfuegbar();
	}break;
	}
}
