#include "View.h"

View::View(std::shared_ptr<Data> data)
{
	Daten		 = data;
	Eingabe		 = 0;
	ZuRenderndesMenu = hauptmenu;
}

View::~View()
{
}

bool View::getSpielIstAktiv()
{
	return (Eingabe == AUSWAHL_BEENDEN) ? false : true;
}

int View::getLetzteNutzerEingabe()
{
	return Eingabe;
}

void View::addBenarichtigung(std::string benarichtigungsText,
			     int benarichtigungsArt, bool gutfuerSpieler)
{
}

void View::ungueltigeEingabe()
{
	std::system("clear");

	std::cout << "Deine Letzte Eingabe ist ungultig!"
		  << "\n BITTE gib eine von den Zahlen ein die zwischen den ( "
		     "Zahl ) steht um die dahinter stehende Aktion auszuführen."
		  << "Die Einzige Auszahme sind die Zahlen 1-9 die für "
		     "bestimmte Menus reserviert sind und von überall als "
		     "Shortcut verfügbar sind.";
}

void View::printKopfZeile(std::string titel)
{
	std::cout << "Kontostand: " << Daten->getKontostand()
		  << "\t Menu: " << titel
		  << "\t Tag: " << Daten->getAnzahlTage();
}

void View::printFussZeile()
{
	std::cout << "\n\n\n"
		  << "Um das Spiel zu beenden " << AUSWAHL_BEENDEN << "\n"
		  << "Um zu Speichern " << AUSWAHL_SPEICHERN << "\n";
}

void View::printGebaeudeStats(GebaeudeUpgradeStats stats, std::string zeitText,
			      std::string spzifischText, std::string kostenText)
{
	std::cout << "(" << AUSWAHL_UPGRADE_ZEIT << ") " << zeitText
		  << "(Kostet:" << stats.BeschlaunigunsKosten
		  << ", Effekt: " << stats.BeschlaunigungsFaktor
		  << "% schneller)\n"
		  << "(" << AUSWAHL_UPGRADE_SPEZIFISCH << ") " << spzifischText
		  << "(Kostet:" << stats.GebaudeSpezielleKosten
		  << ", Effekt: " << stats.GebaudeSpezielleFaktor
		  << "% schneller)\n"
		  << "(" << AUSWAHL_UPGRADE_KOSTEN << ") " << kostenText
		  << "(Kostet:" << stats.AusführungsReduzierungsKosten
		  << ", Effekt: " << stats.AusführungsReduzierungsFaktor
		  << "% schneller)\n";
}

int View::dialogAuswahlEinheit(std::string verwendungszweck)
{
	std::system("clear");
	printKopfZeile("Einheits Auswahlmenu");

	std::cout
	    << "Sie wollen ein Einheit auswählen für " << verwendungszweck
	    << "\n << Bitte geben Sie ein nach welchen Kriterien die Einheiten "
	       "Gefiltert und Angezeigt werden sollen: "
	    << " u für Unverletzte Einheiten,\n"
	    << " v für Verletzte Einheiten "
	    << " t für nicht volle truppenmoral,\n"
	    << " s für Einheiten mit einer min. Starke(in einem zeiten schritt "
	       "werden sie gebeten diese Anzugeben) "
	    << "Sie können mehrere Kriterien gleichzeitig Angeben z. B. vs für "
	       "Verletzte Einheiten mit einer bestimmten mindest Starke.";
	std::string suchKriterien = "";
	std::cin >> suchKriterien;

	leeren();

	/********************************************
	 * Ab hier werden die Einheiten heraus gesucht *
	 ********************************************/

	bool verletzte = false;
	bool gesunde   = false;

	for (size_t i = 0; i < suchKriterien.size(); i++)
	{
		if (suchKriterien[i] == "t")
		{
			sucheNachTruppenmoral();
		}

		if (suchKriterien[i] == "s")
		{
			std::cout << "Was ist die mindest Starke?\n";

			int min = 0;
			std::cin >> min;
			sucheNachStarke(min);
		}

		if (suchKriterien[i] == "u")
		{
			gesunde = true;
		}
		if (suchKriterien[i] == "v")
		{
			verletzte = true;
		}
	}

	if (gesunde && verletzte)
	{
		std::cout << "Es gibt keine Einheit die gesund und verletzt "
			     "gleichzeitig ist.";
		return dialogAuswahlEinheit("Erneute Einheits Auswahl");
	}

	if (gesunde)
	{
		sucheNachUnverletztenEinheiten();
	}

	if (verletzte)
	{
		sucheNachVerletzten();
	}

	/******************************************
	 * Ab hier werden die Einheiten sortiert. *
	 ******************************************/

	std::cout << "Wie sollen die Einheiten sortiert werden? \n"
		  << "n für nicht sortieren, \n"
		  << "s für nach Starke sortieren,\n"
		  << "v für nach den Grad der Verletzung, \n"
		  << "t für nach Moral sortieren.\n";

	char sortierKriterium;
	bool aufsteigen = false;

	std::cin >> sortierKriterium;

	if (sortierKriterium != 'n')
	{
		std::cout << "Soll Auf(1) oder Absteigend(0) sortiert werden.";
		std::cin >> aufsteigen;
	}
	if (sortierKriterium == 's')
	{
		sortiereNachStarke(aufsteigen);
	}
	if (sortierKriterium == 'v')
	{
		sortiereNachVerletzten(aufsteigen);
	}
	if (sortierKriterium == 't')
	{
		sortiereNachTruppenmoral(aufsteigen);
	}

	/******************************************
	 * Ab hier werden die Einheiten Angezeigt *
	 ******************************************/

	std::vector<int> anzuzeigendeEinheiten = getAusgewahlteEinheiten();

	std::cout << "Bitte wahle eine der nachfolgenden Einheiten aus:\n";

	for (size_t i; i < anzuzeigendeEinheiten.size(); i++)
	{
		std::cout
		    << "\n -------------" << i << "-------------- \n"
		    << "Name: "
		    << Daten->getEinheiten()[anzuzeigendeEinheiten[i]].getName()
		    << "Anzahl an Lebenspunkte: "
		    << Daten->getEinheiten()[anzuzeigendeEinheiten[i]]
			   .getLeben()
		    << "Die Truppenmoral: "
		    << Daten->getEinheiten()[anzuzeigendeEinheiten[i]]
			   .getMoral()
		    << "Die Truppenstarke: "
		    << Daten->getEinheiten()[anzuzeigendeEinheiten[i]]
			   .getStarke()
		    << "Das Erfahrungslevel: "
		    << Daten->getEinheiten()[anzuzeigendeEinheiten[i]]
			   .getLevel();
	}

	int ausgewählteEinheit = 0;
	std::cin >> ausgewählteEinheit;

	return anzuzeigendeEinheiten[ausgewählteEinheit];
}

void View::ausgabe(Menus aktuellesMenu, GebaeudeUpgradeStats stats)
{
	ZuRenderndesMenu = aktuellesMenu;
	std::system("clear");

	switch (ZuRenderndesMenu)
	{
	case hauptmenu:
	{
		printKopfZeile("Hauptmenu");

		std::cout << "Was möchten Sie machen? \n\n"
			  << "(" << AUSWAHL_MENU_ZENTRALE
			  << ") Die Zentrale betreten\n"
			  << "(" << AUSWAHL_MENU_BATILIONAUSBILDUNGSZENTRUM
			  << ") Das Batillion Ausbildungszentrum betreten"
			  << "(" << AUSWAHL_MENU_SCOUTBUERO
			  << ") Das Scoutbuero betreten\n"
			  << "(" << AUSWAHL_MENU_ERHOLUNGSRESORT
			  << ") Das Erholungsresort betreten\n"
			  << "(" << AUSWAHL_MENU_TRANINGSZENTRUM
			  << ") Das Traningszentrum betreten\n"
			  << "(" << AUSWAHL_MENU_VERFUEGBARE_AUFTRAGE
			  << ") Die Verfuegbare Auftraege betreten\n"
			  << "(" << AUSWAHL_MENU_LAUFENDE_AUFTRAGE
			  << ") Die Angenohmmenen Auftragsuebersicht betreten\n"
			  << "(" << AUSWAHL_MENU_LOGISTIK_SYSTEM
			  << ") Das Logistik System betreten\n";

		printFussZeile();

		std::cin >> Eingabe;
	}
	break;
	case batillionsausbildungsstate:
	{
		printKopfZeile("Batilionsausbildungszentrum");

		std::cout << "Was möchten Sie machen? \n\n"
			  << "(" << AUSWAHL_AKTION_1
			  << ") Ausbildung der Einheit starten\n"
			  << "(" << AUSWAHL_AKTION_2
			  << ") Mehr Truppenmitglieder ausbilden"
			  << "(" << AUSWAHL_AKTION_3
			  << ") Weniger Truppenmitglieder ausbilden\n";

		printGebaeudeStats(
		    stats, "[Upgrade] Verkürzung der Ausbildungsdauer",
		    "[Upgrade] Die Grundstaerke der Truppe verbessern",
		    "[Upgrade] Ausbildungskosten reduzierung");

		// XXX: Ausgabe der aktuellen Werte, wie ein Batelion aussieht
		// wenn sie jetz ausgebildet wird

		printFussZeile();

		std::cin >> Eingabe;
	}
	break;
	case scoutbuero:
	{
		printKopfZeile("Scoutbüro");

		std::cout << "Was möchten Sie machen? \n\n"
			  << "(" << AUSWAHL_AKTION_1
			  << ") Suche nach einen guten Kämpfer starten)\n";

		printGebaeudeStats(
		    stats, "[Upgrade] Verkürzen der Suchdauer",
		    "[Upgrade] Bessere Kämpfer finden und anwerben(Höhere "
		    "Rang)",
		    "[Upgrade] Die Kosten für die Suche reduzieren");

		// XXX: Ausgabe der aktuellen Werte, wie die Suche aussieht wenn
		// sie jetz gestartet wird

		printFussZeile();

		std::cin >> Eingabe;
	}
	break;
	case traningszentrum:
	{
		printKopfZeile("Traningszentrum");

		std::cout << "Was möchten Sie machen? \n\n"
			  << "(" << AUSWAHL_AKTION_1
			  << ") Ein intensiv Traening starten\n"
			  << "(" << AUSWAHL_AKTION_2
			  << ") Ein gutes grundlagen Traning starten"
			  << "(" << AUSWAHL_AKTION_3
			  << ") Einmal kurz ins Gym\n";

		printGebaeudeStats(
		    stats, "[Upgrade] Verkürzung der Traningsdauer",
		    "[Upgrade] Die Traningsmethoden verbessern",
		    "[Upgrade] Die Kosten fuer ein Traning senken");

		printFussZeile();

		std::cin >> Eingabe;
	}
	break;
	case erholungsresort:
	{
		printKopfZeile("Erholungsresort");

		std::cout
		    << "Was möchten Sie machen? \n\n"
		    << "(" << AUSWAHL_AKTION_1
		    << ") Eine Einheit zum erholen(HP und Moral) auswahlen";

		printGebaeudeStats(stats,
				   "[Upgrade] Verkürzung der Erholngsdauer",
				   "[Upgrade] Die Resort Qualität verbessern",
				   "[Upgrade] Resortkosten reduzieren");

		printFussZeile();

		std::cin >> Eingabe;
	}
	break;
	default:
	{
	}
	break;
	}

	if (Eingabe == AUSWAHL_HILFE)
	{
		dialogHilfe();
	}
}

void View::dialogHilfe()
{
	std::cout << "Wilkommen im Hilfsmenu. \n Aktuell gibt es keine "
		     "Eintrage zum Menu in dem du dich befindest, daher kann "
		     "ich dir leider nicht helfen :( . ";
}
