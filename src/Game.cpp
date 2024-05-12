#include "Game.h"

Game::Game()
{
	Daten = std::make_shared<Data>();

	//Gebaude
	BAZ = new Batillion_Ausbildungszentrum(Daten);

	Scoutbueros = new Scoutbuero(Daten);

	Traningzentren = new Traningszentrum(Daten);

	Hauptquatier = new Zentrale(Daten);

	Erholungsresorts = new Erholungsresort(Daten);

	view = std::make_unique<View>(Daten);

	ZeitpunktDesLetztenTages = std::chrono::steady_clock::now();

	AktuellesMenu = hauptmenu;

	Stats = GebaeudeUpgradeStats();
}

Game::~Game()
{
	delete BAZ;
	delete Scoutbueros;
	delete Traningzentren;
	delete Hauptquatier;
	delete Erholungsresorts;
}

void Game::spielLauft()
{
	while (view->getSpielIstAktiv())
	{
		update();

		zeit();

		view->ausgabe(AktuellesMenu, Stats);
	}

	Daten->saveGameToFile();
}

void Game::update()
{
	int eingabe = view->getLetzteNutzerEingabe();

	if (eingabe == AUSWAHL_SPEICHERN)
	{
		Daten->saveGameToFile();
	}

	switch (AktuellesMenu) // @suppress("Missing cases in switch")  @suppress("Missing default in switch")     Unterdrücken beider Sachen da das Einzige nicht entahltene hauptmenu ist was danach bearbeitet wird und es keinen sinnvollen defult gibt.
	{
	case zentrale:
	{

	}
		break;

	case batillionsausbildungsstate:
	{

		switch (eingabe)
		{
		case AUSWAHL_AKTION_1:
		{
			BAZ->beginneAufgabe();	//starten Gedr�kt
		}
			break;
		case AUSWAHL_AKTION_2:
		{
			BAZ->erhoheEinheitsGrosse();		//Anzahl Mitglieder wird erh�ht
		}
			break;
		case AUSWAHL_AKTION_3:
		{
			BAZ->reduziereEinheitsGrosse();	//Anzahl der Mitglieder wird gesengt
		}
			break;
		case AUSWAHL_UPGRADE_ZEIT:
		{
			BAZ->beschleunigungDerAufgabenDurchfuehrung();//Upgrade Geschwindikeit
		}
			break;
		case AUSWAHL_UPGRADE_SPEZIFISCH:
		{
			BAZ->erhohenDerGrundstarke();	 //Upgrade Grundst�rke
		}
			break;
		case AUSWAHL_UPGRADE_KOSTEN:
		{
			BAZ->reduzierenDerAusfuhrungsKosten();//Upgrade zur kosten Reduzierung
		}
			break;
		default:
		{
			view->ungueltigeEingabe();
		}
			break;
		}

		Stats = BAZ->getUpgradeStats();
	}
		break;

	case scoutbuero:
	{
		switch (eingabe)
		{
		case AUSWAHL_AKTION_1:
		{
			Scoutbueros->beginneAufgabe();				// Suche Starten
		}
			break;
		case AUSWAHL_UPGRADE_ZEIT:
		{
			Scoutbueros->beschleunigungDerAufgabenDurchfuehrung();// Beschleunigt die Suche
		}
			break;
		case AUSWAHL_UPGRADE_SPEZIFISCH:
		{
			Scoutbueros->erhohenDesMoeglichenRanges();// Erh�ht den mindest Rang
		}
			break;
		case AUSWAHL_UPGRADE_KOSTEN:
		{
			Scoutbueros->reduzierenDerAusfuhrungsKosten();// Reduzierung der Suchkosten
		}
			break;
		case 25:
		{
			Scoutbueros->annehmenDerEinheit();					// Annehmen
		}
			break;
		case 26:
		{
			Scoutbueros->ablehnenDerEinheit();					// Ablehnen
		}
			break;
		default:
		{
			view->ungueltigeEingabe();
		}
			break;
		}

		Stats = Scoutbueros->getUpgradeStats();
	}
		break;

	case traningszentrum:
	{
		switch (eingabe)
		{
		case AUSWAHL_UPGRADE_ZEIT:
		{
			Traningzentren->beschleunigungDerAufgabenDurchfuehrung();
		}
			break;
		case AUSWAHL_UPGRADE_SPEZIFISCH:
		{
			Traningzentren->erhohenDerTraningsWirksamkeit();
		}
			break;
		case AUSWAHL_UPGRADE_KOSTEN:
		{
			Traningzentren->reduzierenDerAusfuhrungsKosten();
		}
			break;
		case AUSWAHL_AKTION_1:
		{
			Traningzentren->langeTrainingsDauer();
			int ausgewaelteEinheit = view->dialogAuswahlEinheit("ein langes Traning");
		}
			break;
		case AUSWAHL_AKTION_3:
		{
			Traningzentren->kurzeTraningsDauer();
			int ausgewaelteEinheit = view->dialogAuswahlEinheit("ein kurzes Traning");
		}
			break;
		case AUSWAHL_AKTION_2:
		{
			Traningzentren->mittlereTrainingsDauer();
			int ausgewaelteEinheit = view->dialogAuswahlEinheit("ein mittellanges Traning");
		}
			break;
		default:
		{
			view->ungueltigeEingabe();
		}
			break;
		}

		Stats = Traningzentren->getUpgradeStats();
	}
		break;

	case erholungsresort:
	{
		switch (eingabe)
		{
		case AUSWAHL_AKTION_1:
		{
			int ausgewaelteEinheit = view->dialogAuswahlEinheit("eine Erholung");
		}
			break;
		case AUSWAHL_UPGRADE_ZEIT:
		{
			Erholungsresorts->beschleunigungDerAufgabenDurchfuehrung();
		}
			break;
		case AUSWAHL_UPGRADE_SPEZIFISCH:
		{
			Erholungsresorts->erhohenDerTraningsWirksamkeit();
		}
			break;
		case AUSWAHL_UPGRADE_KOSTEN:
		{
			Erholungsresorts->reduzierenDerAusfuhrungsKosten();
		}
			break;

			break;
		default:
		{
			view->ungueltigeEingabe();
		}
			break;
		}

		Stats = Erholungsresorts->getUpgradeStats();
	}
		break;
	}

	//Das Switch Statement ist zum einen das Hauptmenu zum andern ermöglicht es 'Shortcuts' sodass man immer die Zahl für AUSWAHL_MENU_ZENTRALE eingeben kann und im nächsten frame sich in der Zentrale befindet.
	switch (eingabe)
	{
	case AUSWAHL_MENU_ZENTRALE:
	{
		AktuellesMenu = zentrale;
	}
		break;
	case AUSWAHL_MENU_BATILIONAUSBILDUNGSZENTRUM:
	{
		AktuellesMenu = batillionsausbildungsstate;
	}
		break;
	case AUSWAHL_MENU_TRANINGSZENTRUM:
	{
		AktuellesMenu = traningszentrum;
	}
		break;
	case AUSWAHL_MENU_SCOUTBUERO:
	{
		AktuellesMenu = scoutbuero;
	}
		break;
	case AUSWAHL_MENU_ERHOLUNGSRESORT:
	{
		AktuellesMenu = erholungsresort;
	}
		break;
	case AUSWAHL_MENU_VERFUEGBARE_AUFTRAGE:
	{
		AktuellesMenu = auftraege;
	}
		break;
	case AUSWAHL_MENU_LAUFENDE_AUFTRAGE:
	{
		AktuellesMenu = aauftraege;
	}
		break;
	case AUSWAHL_MENU_LOGISTIK_SYSTEM:
	{
		AktuellesMenu = logistikSystem;
	}
		break;
	default:
	{
		AktuellesMenu = hauptmenu;
	}
		break;
	}

}

void Game::zeit()
{
	float delta_time = 1;
	//{ std::chrono::duration_cast<std::chrono::seconds>( std::chrono::steady_clock::now() - ZeitpunktDesLetztenTages) };	FIXME: make time comparison possible

	if (delta_time >= Daten->getTagesDauer())
	{
		Daten->erhoheAnzahlTage();

		BAZ->aktualisierenTimer();
		Scoutbueros->aktualisierenTimer();
		Traningzentren->aktualisierenTimer();
		Erholungsresorts->aktualisierenTimer();

		if (Daten->getAnzahlTage() % Daten->getMONATS_DAUER() == 0)
		{
			//Sold auszahlen
		}

		ZeitpunktDesLetztenTages = std::chrono::steady_clock::now();
	}
}
