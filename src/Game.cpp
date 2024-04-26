#include "PreHeader.h"
#include "Game.h"

Game::Game()
{
	Daten = std::make_shared<Data>();
	
	//Gebaude
	BAZ = new Batillion_Ausbildungszentrum(Daten);
	
	Scoutbueros = new Scoutbuero(Daten);

	Traningzentren = new Traningszentrum(Daten);

	Zentrale = new Zentale(Daten);

	Erholungsresorts = new Erholungsresort(Daten);
	
	//Auswahl
	Tag = 0;
	Auswahl = false;

	View = std::make_unique<View>(Daten);
}

Game::~Game()
{
	delete BAZ;
	delete Scoutbueros;
	delete Traningzentren;
	delete Zentrale;
	delete Erholungsresorts;
}

void Game::SpielLauft()
{
	while (View->getWindow().isOpen())
	{
		update();
		
		checkSortcuts();

		Zeit();

		if (View->getWindow().isOpen())
		{
			//Daten->getAnimationen().Aktualisieren(View->getMousPos());	TODO UI Animation

			mahlen();
		}
	}
}

void Game::TextAnzeigeinitzaliesieren()
{
	//Hauptmenu erste Zeile
	Daten->getKacheln(0).TextAendern("Zentrale", 250);
	Daten->getKacheln(1).TextAendern("Batillionausbildungszentrum", 250);
	Daten->getKacheln(2).TextAendern("Trainingszentrum", 250);
	Daten->getKacheln(3).TextAendern("Scout Buero", 250);
	//Hauptmenu zweite Zeile
	Daten->getKacheln(4).TextAendern("Auftraege", 255 + 220);
	Daten->getKacheln(5).TextAendern("Aktive Auftraege", 255 + 220);
	Daten->getKacheln(6).TextAendern("Logistik System", 255 + 220);
	Daten->getKacheln(7).TextAendern("Erholungsresort", 255 + 220);
	//BAZ
	Daten->getKacheln(9) .TextAendern("Beschleunigt die\nAusbildungsdauer um 5%\n Kosten 100", 350);
	Daten->getKacheln(10).TextAendern("Erhoehung der Grundstaerke\nKosten 100", 350);
	Daten->getKacheln(11).TextAendern("Reduzierung der Kosten\nKosten 100", 350);
	//Scoutbuero
	Daten->getKacheln(12).TextAendern("Einselkaempfer Rekutieren\n(EM)\nEin EM bekommt\nein Teil der Finanzellen\nBehlohnung und hat\neine Affinitaet.\nDie Affinitaet erlaubt\ndie Ausstatung spezieller\nWaffen und bringt\nVorteile bei bestimmten\nAuftragen.", 200);
	Daten->getKacheln(13).TextAendern("Beschleungigt die\nSuche um 5%\nKosten: 100", 350);
	Daten->getKacheln(14).TextAendern("Das Scoutbuero\nfindet Einselkampfer die\neinen hohren Rang\nund Potenzial habne\nKosten: 100", 320);
	Daten->getKacheln(15).TextAendern("Reduzierung der Kosten\nKosten: 100", 350);
}

void Game::update()
{
	{
		//std::lock_guard<std::mutex> lock(mSicherung);
		vMauspos = View->getMousPos();
	}

	switch (AktuellesMenu)
	{
		
	case Hauptmenu:
	{
		int temp = 1;
		//std::lock_guard<std::mutex> lock(mSicherung);
		for (int i = 0; i < 8; i++)
		{
			if (Daten->getHauptmenu(i).MausSchwebtDrueber(vMauspos))
			{
				if (Daten->getHauptmenu(i).getTextureGroessenSkalierungsFaktor() < 1.1)
				{
					Daten->getHauptmenu(i).setTextureGroessenSkalierungsFaktor(Daten->getKacheln(i).getTextureGroessenSkalierungsFaktor() + 0.01);
					Daten->getHauptmenu(i).setTexturePosition(sf::Vector2f(Daten->getKacheln(i).getTexturePosition().x-1, Daten->getKacheln(i).getTexturePosition().y - 2));
				}

				if (Daten->getHauptmenu(i).wirdGedruedckt())
				{
					Daten->getHauptmenu(i).setKachel_Gedruecktfarbe();
					switch (Daten->getHauptmenu(i).getID())
					{
					case 1: {
						AktuellesMenu = Zentrale;
					}break;
					case 2: {
						AktuellesMenu = Batillionsausbildungsstate;
					}break;
					case 3: {
						AktuellesMenu = traningszentrum;
					}break;
					case 4: {
						AktuellesMenu = scoutbuero;
					}break;
					case 5: {
						AktuellesMenu = erholungsresort;
					}break;
					case 6: {
						AktuellesMenu = Auftraege;
					}break;
					case 7: {
						AktuellesMenu = AAuftraege;
					}break;
					case 8: {
						AktuellesMenu = LogistikSystem;
					}break;
					}
				}
				else
					Daten->getHauptmenu(i).setKachel_Schwebefarbe();

			}
			else
			{
				Daten->getHauptmenu(i).setTextureGroessenSkalierungsFaktor(1);
				Daten->getHauptmenu(i).setKachel_Hintergrundfarbe();
				if (i < 4)
					Daten->getHauptmenu(i).setTexturePosition(sf::Vector2f(i * Daten->getBreite() + (i + 1) * 20 + 15, 70));

				else
				{
					Daten->getHauptmenu(i).setTexturePosition(sf::Vector2f(temp * Daten->getBreite() + (temp + 1) * 20 + 15, Daten->getHohe()+90));
				}
			}

			if (i > 3)
				temp++;
		}
	}break;
	
	case zentrale:
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

	case Batillionsausbildungsstate:
	{
		int temp = 0;
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			temp = (Daten->getAnimationen().getKeineBenarichtigung())?99: updateButtons(8, 4);
		}
		switch (temp)	// Bestimmen welcher Butten gedr�ckt wurde 
		{
		case 1: 
		{
			BAZ->BeginnAufgabe();	//starten Gedr�kt
		}break;
		case 11: 
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			BAZ->AnzahlErhohen();		//Anzahl Mitglieder wird erh�ht
		}break;
		case 12: 
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			BAZ->AnzahlReduzieren();	//Anzahl der Mitglieder wird gesengt
		}break;
		case 2: 
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			BAZ->BeschleunigungDerAufgabenDurchfuehrung();	//Upgrade Geschwindikeit
		}break;
		case 3:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			BAZ->ErhohenDerGrundstarke();	 //Upgrade Grundst�rke
		}break;
		case 4: 
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			BAZ->ReduzierenDerAusfuhrungsKosten();		//Upgrade zur kosten Reduzierung
		}break;
		case 5:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			BAZ->Vorbereiten_neueAusbildung();
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
			Scoutbueros->BeginnAufgabe();				// Suche Starten
		}break;
		case 2:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			Scoutbueros->BeschleunigungDerAufgabenDurchfuehrung();	// Beschleunigt die Suche
		}break;
		case 3:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			Scoutbueros->ErhohenDesMoeglichenRanges();				// Erh�ht den mindest Rang
		}break;
		case 4:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			Scoutbueros->ReduzierenDerAusfuhrungsKosten();			// Reduzierung der Suchkosten
		}break;
		case 5:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			Scoutbueros->Annehmen();					// Annehmen
		}break;
		case 6:
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			Scoutbueros->Ablehnen();					// Ablehnen
		}break; 
		}
	}break;

	case traningszentrum:
	{
		if (Auswahl)
		{
			auto temp = Traningzentren->updateAuswahl(vMauspos);
			if (temp.has_value())
			{
				Traningzentren->AuswahlZuOrdnen(temp.value());
				Auswahl = false;
			}
		}

		else
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			switch (updateButtons(16, 4))
			{
			case 2:
			{
				Traningzentren->BeschleunigungDerAufgabenDurchfuehrung();
			}break;
			case 3:
			{
				Traningzentren->ErhohenDerTraningsWirksamkeit();
			}break;
			case 4:
			{
				Traningzentren->ReduzierenDerAusfuhrungsKosten();
			}break;
			case 5:
			{
				Traningzentren->LangeTrainingsDauer();
				Auswahl = true;
			}break;
			case 6:
			{
				Traningzentren->KurzeTraningsDauer();
				Auswahl = true;
			}break;
			case 7:
			{
				Traningzentren->MittlereTrainingsDauer();
				Auswahl = true;
			}break;
			}
		}
	}break;

	case erholungsresort:
	{
		if (Auswahl)
		{
			auto temp = Erholungsresorts->updateAuswahl(vMauspos);
			if (temp.has_value())
			{
				Erholungsresorts->AuswahlZuOrdnen(temp.value());
				Auswahl = false;
			}
		}

		else
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			switch (updateButtons(24, 4))
			{
			case 2:
			{
				Erholungsresorts->BeschleunigungDerAufgabenDurchfuehrung();
			}break;
			case 3:
			{
				Erholungsresorts->ErhohenDerTraningsWirksamkeit();
			}break;
			case 4:
			{
				Erholungsresorts->ReduzierenDerAusfuhrungsKosten();
			}break;

			case 5:
				Erholungsresorts->leeren();
				Erholungsresorts->SucheNachEinsetzbarenEinheiten();
				Auswahl = true;
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
		Daten->getKacheln(i).aktualisieren();
		//Kacheln ueberpruefen
		if (Daten->getKacheln(i).MausSchwebtDrueber(vMauspos))
		{
			Daten->getKacheln(i).setKachel_Schwebefarbe();
			//Butten ueberpruefen
			 iButtenID = Daten->getKacheln(i).ueberprueftAlleButtonObMausSchwebtDrueber(vMauspos);
			if (iButtenID.has_value())
				if (Daten->getKacheln(i).ueberprueftButtonObGedruektWird(iButtenID.value()))
					bButtenGedrueckt = true;
				else {}
			else
				Daten->getKacheln(i).setAlleButtenAufHintergrundfarbe();
		}
		else
		{
			Daten->getKacheln(i).setKachel_Hintergrundfarbe();
			Daten->getKacheln(i).setTextureGroessenSkalierungsFaktor(1);
		}
		//lockguard.~lock_guard();
	}
	return bButtenGedrueckt ? iButtenID.value() : 99;
}

void Game::checkSortcuts()
{
	sf::Event event;
	while (View->getWindow().pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			View->getWindow().close();
		}

		else if (event.type == sf::Event::Resized)
		{
			sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
			View->getWindow().setView(sf::View(visibleArea));

			View->ReSize();
		}

		else if (event.type == sf::Event::TextEntered)
		{
			if (Daten->getKacheln(8).getTextfeldAusgewahltStatus()||Daten->getKacheln(8).ueberpruefenObEnterGedruekt(event))
				Daten->getKacheln(8).aktualisierenTextfelder(event, sf::Mouse::getPosition(View->getWindow()));

			else
			{
				if (cKeyboard.isKeyPressed(cKeyboard.Escape))
					View->getWindow().close();

				if (cKeyboard.isKeyPressed(cKeyboard.H))
					AktuellesMenu = Hauptmenu;

				if (cKeyboard.isKeyPressed(cKeyboard.Z))
					AktuellesMenu = Zentrale;

				if (cKeyboard.isKeyPressed(cKeyboard.A))
					AktuellesMenu = Batillionsausbildungsstate;

				if (cKeyboard.isKeyPressed(cKeyboard.S))
					AktuellesMenu = scoutbuero;
			}
		}
	}
}

void Game::Zeit()
{
	if (clTagesTimer.getElapsedTime().asSeconds() >= 1.5)
	{
		Tag++;

		{
			//std::lock_guard<std::mutex> lock(mSicherung);
			BAZ->aktualisierenTimer();
			Scoutbueros->aktualisierenTimer();
			Traningzentren->aktualisierenTimer();
			Erholungsresorts->aktualisierenTimer();
		}

		if (Tag % 30 == 0)
		{
			//Sold auszahlen
		}
		clTagesTimer.restart();
	}
}

void Game::mahlen()
{
	switch (AktuellesMenu)
	{
	case Hauptmenu: 
	{           
		View->DrawHauptmenu(Tag);
	}break;
	case Batillionsausbildungsstate:
	{
		View->DrawBAZ(Tag);
	}break;
	case scoutbuero:
	{
		View->DrawScoutbuero(Tag);
	}break;
	case traningszentrum:
	{
		if (!Auswahl)
			View->DrawTraningszentrum(Tag);
		else
			View->DrawDiffrent(*Traningzentren);
	}break;
	case erholungsresort:
	{
		if (!Auswahl)
			View->DrawErholungsresort(Tag);
		else
			View->DrawDiffrent(*Erholungsresorts);
	}break;
	default: {
		View->DrawNichtVerfuegbar();
	}break;
	}
}
