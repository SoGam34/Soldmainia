#include "Game.h"
#include "Menus.h"
#include <sstream>

Game::Game()
{
	Daten = std::make_shared<Data>();

	// Gebaude
	BAZ = new Batillion_Ausbildungszentrum(Daten);

	Scoutbueros = new Scoutbuero(Daten);

	Traningzentren = new Traningszentrum(Daten);

	Hauptquatier = new Zentrale(Daten);

	Erholungsresorts = new Erholungsresort(Daten);

	view = std::make_unique<View>(Daten);

	//XXX(Time): Initilize Timer
	ZeitpunktDesLetztenTages = std::chrono::steady_clock::now();

	AktuellesMenu = hauptmenu;

	Stats = GebaeudeUpgradeStats();
	Progress = InProgressStats();
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

		view->ausgabe(AktuellesMenu, Stats, Progress);
	}

	Daten->saveGameToFile();
}

void Game::update()
{
	int const eingabe = view->getLetzteNutzerEingabe();

	if (eingabe == AUSWAHL_SPEICHERN)
	{
		Daten->saveGameToFile();
		return;
	}

	switch (
	    AktuellesMenu) 
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
			BAZ->beginneAufgabe();
			std::stringstream temp;
			temp << "Kosten: "
			     << BAZ->getGebaeudeAusfuhrungskosten();
			view->addBenarichtigung(temp.str(), 0, false);
		}
		break;
		case AUSWAHL_AKTION_2:
		{
			BAZ->erhoheEinheitsGrosse();
		}
		break;
		case AUSWAHL_AKTION_3:
		{
			BAZ->reduziereEinheitsGrosse();
		}
		break;
		case AUSWAHL_UPGRADE_ZEIT:
		{
			// TODO(Kosten): Benarichtigung
			BAZ->beschleunigungDerAufgabenDurchfuehrung();
		}
		break;
		case AUSWAHL_UPGRADE_SPEZIFISCH:
		{
			// TODO(Kosten): Benarichtigung
			BAZ->erhohenDerGrundstarke();
		}
		break;
		case AUSWAHL_UPGRADE_KOSTEN:
		{
			// TODO(Kosten): Benarichtigung
			BAZ->reduzierenDerAusfuhrungsKosten();
		}
		break;
		default:
		{
			view->ungueltigeEingabe();
		}
		break;
		}

		Stats	 = BAZ->getUpgradeStats();
		Progress = BAZ->getProgressStats();
	}
	break;

	case scoutbuero:
	{
		switch (eingabe)
		{
		case AUSWAHL_AKTION_1:
		{
			Scoutbueros->beginneAufgabe(); // Suche Starten
		}
		break;
		case AUSWAHL_UPGRADE_ZEIT:
		{
			// TODO(Kosten): Benarichtigung
			Scoutbueros->beschleunigungDerAufgabenDurchfuehrung();
		}
		break;
		case AUSWAHL_UPGRADE_SPEZIFISCH:
		{
			// TODO(Kosten): Benarichtigung
			Scoutbueros->erhohenDesMoeglichenRanges();
		}
		break;
		case AUSWAHL_UPGRADE_KOSTEN:
		{
			// TODO(Kosten): Benarichtigung
			Scoutbueros->reduzierenDerAusfuhrungsKosten();
		}
		break;
		case 25:
		{
			// TODO(Einheit): Benarichtigung
			Scoutbueros->annehmenDerEinheit(); // Annehmen
		}
		break;
		case 26:
		{
			// TODO(Einheit): Benarichtigung
			Scoutbueros->ablehnenDerEinheit(); // Ablehnen
		}
		break;
		default:
		{
			view->ungueltigeEingabe();
		}
		break;
		}

		Stats	 = Scoutbueros->getUpgradeStats();
		Progress = Scoutbueros->getProgressStats();
	}
	break;

	case traningszentrum:
	{
		switch (eingabe)
		{
		case AUSWAHL_UPGRADE_ZEIT:
		{
			// TODO(Kosten): Benarichtigung
			Traningzentren
			    ->beschleunigungDerAufgabenDurchfuehrung();
		}
		break;
		case AUSWAHL_UPGRADE_SPEZIFISCH:
		{
			// TODO(Kosten): Benarichtigung
			Traningzentren->erhohenDerTraningsWirksamkeit();
		}
		break;
		case AUSWAHL_UPGRADE_KOSTEN:
		{
			// TODO(Kosten): Benarichtigung
			Traningzentren->reduzierenDerAusfuhrungsKosten();
		}
		break;
		case AUSWAHL_AKTION_1:
		{
			Traningzentren->langeTrainingsDauer();
			int ausgewaelteEinheit 
			    {view->dialogAuswahlEinheit("ein langes Traning")};
			Traningzentren->auswahlZuOrdnen(ausgewaelteEinheit);
		}
		break;
		case AUSWAHL_AKTION_3:
		{
			Traningzentren->kurzeTraningsDauer();
			int ausgewaelteEinheit =
			    view->dialogAuswahlEinheit("ein kurzes Traning");
			Traningzentren->auswahlZuOrdnen(ausgewaelteEinheit);
		}
		break;
		case AUSWAHL_AKTION_2:
		{
			Traningzentren->mittlereTrainingsDauer();
			int ausgewaelteEinheit = view->dialogAuswahlEinheit(
			    "ein mittellanges Traning");
			Traningzentren->auswahlZuOrdnen(ausgewaelteEinheit);
		}
		break;
		default:
		{
			view->ungueltigeEingabe();
		}
		break;
		}

		Stats	 = Traningzentren->getUpgradeStats();
		Progress = Traningzentren->getProgressStats();
	}
	break;

	case erholungsresort:
	{
		switch (eingabe)
		{
		case AUSWAHL_AKTION_1:
		{
			int ausgewaelteEinheit =
			    view->dialogAuswahlEinheit("eine Erholung");
			Erholungsresorts->auswahlZuOrdnen(ausgewaelteEinheit);
		}
		break;
		case AUSWAHL_UPGRADE_ZEIT:
		{
			// TODO(Kosten): Benarichtigung
			Erholungsresorts
			    ->beschleunigungDerAufgabenDurchfuehrung();
		}
		break;
		case AUSWAHL_UPGRADE_SPEZIFISCH:
		{
			// TODO(Kosten): Benarichtigung
			Erholungsresorts->erhohenDerTraningsWirksamkeit();
		}
		break;
		case AUSWAHL_UPGRADE_KOSTEN:
		{
			// TODO(Kosten): Benarichtigung
			Erholungsresorts->reduzierenDerAusfuhrungsKosten();
		}
		break;
		default:
		{
			view->ungueltigeEingabe();
		}
		break;
		}

		Stats	 = Erholungsresorts->getUpgradeStats();
		Progress = Erholungsresorts->getProgressStats();
	}
	break;
	}

	// Das Switch Statement ist zum einen das Hauptmenu zum andern
	// ermöglicht es 'Shortcuts' sodass man immer die Zahl für
	// AUSWAHL_MENU_ZENTRALE eingeben kann und im nächsten frame sich in der
	// Zentrale befindet.
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
	//{ std::chrono::duration_cast<std::chrono::seconds>(
	// std::chrono::steady_clock::now() - ZeitpunktDesLetztenTages) };
	// FIXME: make time comparison possible

	if (delta_time >= Daten->getTagesDauer())
	{
		Daten->erhoheAnzahlTage();

		BAZ->aktualisierenTimer();
		Scoutbueros->aktualisierenTimer();
		Traningzentren->aktualisierenTimer();
		Erholungsresorts->aktualisierenTimer();

		if (Daten->getAnzahlTage() % Daten->getMONATS_DAUER() == 0)
		{
			// Sold auszahlen
		}
		//TODO(Time): Akktualisieren bzw. zurücksetzen des Timers
		ZeitpunktDesLetztenTages = std::chrono::steady_clock::now();
	}
}
