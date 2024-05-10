#include "View.h"

View::View(std::shared_ptr<Data> data)
{
	Daten = data;
	Eingabe = 0;
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

void View::ungueltigeEingabe()
{
	std::system("clear");

	std::cout
			<< "Deine Letzte Eingabe ist ungultig!"
			<< "\n BITTE gib eine von den Zahlen ein die zwischen den ( Zahl ) steht um die dahinter stehende Aktion auszuführen."
			<< "Die Einzige Auszahme sind die Zahlen 1-9 die für bestimmte Menus reserviert sind und von überall als Shortcut verfügbar sind.";
}

void View::printKopfZeile(std::string titel)
{
	std::cout << "Kontostand: " << Daten->getKontostand() << "\t Menu: "
			<< titel << "\t Tag: " << Daten->getAnzahlTage();
}

void View::printFussZeile()
{
	std::cout << "\n\n\n" << "Um das Spiel zu beenden " << AUSWAHL_BEENDEN
			<< "\n" << "Um zu Speichern " << AUSWAHL_SPEICHERN << "\n";
}

void View::printGebaeudeStats(GebaeudeStats stats, std::string zeitText,
		std::string spzifischText, std::string kostenText)
{
	std::cout << "(" << AUSWAHL_UPGRADE_ZEIT << ") " << zeitText << "(Kostet:"
			<< stats.BeschlaunigunsKosten << ", Effekt: "
			<< stats.BeschlaunigungsFaktor << "% schneller)\n" << "("
			<< AUSWAHL_UPGRADE_SPEZIFISCH << ") " << spzifischText << "(Kostet:"
			<< stats.GebaudeSpezielleKosten << ", Effekt: "
			<< stats.GebaudeSpezielleFaktor << "% schneller)\n" << "("
			<< AUSWAHL_UPGRADE_KOSTEN << ") " << kostenText << "(Kostet:"
			<< stats.AusführungsReduzierungsKosten << ", Effekt: "
			<< stats.AusführungsReduzierungsFaktor << "% schneller)\n";
}

int View::einheitsAuswahlMenu(std::vector<int> anzuzeigendeEinheiten)
{
	std::cout << "Bitte wahle eine der nachfolgenden Einheiten aus:\n";

	for(size_t i; i<anzuzeigendeEinheiten.size(); i++)
	{
		std::cout
			<< "\n -------------" << i << "-------------- \n"
			<< "Name: " << Daten->getEinheiten()[anzuzeigendeEinheiten[i]].getName()
			<< "Anzahl an Lebenspunkte: " << Daten->getEinheiten()[anzuzeigendeEinheiten[i]].getLeben()
			<< "Die Truppenmoral: " << Daten->getEinheiten()[anzuzeigendeEinheiten[i]].getMoral()
			<< "Die Truppenstarke: " << Daten->getEinheiten()[anzuzeigendeEinheiten[i]].getStarke()
			<< "Das Erfahrungslevel: " << Daten->getEinheiten()[anzuzeigendeEinheiten[i]].getLevel();
	}

	int ausgewählteEinheit = 0;
	std::cin >> ausgewählteEinheit;

	return anzuzeigendeEinheiten[ausgewählteEinheit];
}

void View::ausgabe(Menus aktuellesMenu, GebaeudeStats stats)
{
	ZuRenderndesMenu = aktuellesMenu;
	std::system("clear");

	switch (ZuRenderndesMenu)
	{
	case hauptmenu:
	{
		printKopfZeile("Hauptmenu");

		std::cout << "Was möchten Sie machen? \n\n" << "("
				<< AUSWAHL_MENU_ZENTRALE << ") Die Zentrale betreten\n" << "("
				<< AUSWAHL_MENU_BATILIONAUSBILDUNGSZENTRUM
				<< ") Das Batillion Ausbildungszentrum betreten" << "("
				<< AUSWAHL_MENU_SCOUTBUERO << ") Das Scoutbuero betreten\n"
				<< "(" << AUSWAHL_MENU_ERHOLUNGSRESORT
				<< ") Das Erholungsresort betreten\n" << "("
				<< AUSWAHL_MENU_TRANINGSZENTRUM
				<< ") Das Traningszentrum betreten\n" << "("
				<< AUSWAHL_MENU_VERFUEGBARE_AUFTRAGE
				<< ") Die Verfuegbare Auftraege betreten\n" << "("
				<< AUSWAHL_MENU_LAUFENDE_AUFTRAGE
				<< ") Die Angenohmmenen Auftragsuebersicht betreten\n" << "("
				<< AUSWAHL_MENU_LOGISTIK_SYSTEM
				<< ") Das Logistik System betreten\n";

		printFussZeile();

		std::cin >> Eingabe;
	}
		break;
	case batillionsausbildungsstate:
	{
		printKopfZeile("Batilionsausbildungszentrum");

		std::cout << "Was möchten Sie machen? \n\n"
				<< "(" << AUSWAHL_AKTION_1	<< ") Ausbildung der Einheit starten\n"
				<< "(" << AUSWAHL_AKTION_2	<< ") Mehr Truppenmitglieder ausbilden"
				<< "(" << AUSWAHL_AKTION_3	<< ") Weniger Truppenmitglieder ausbilden\n";

		printGebaeudeStats(stats,
				"[Upgrade] Verkürzung der Ausbildungsdauer",
				"[Upgrade] Die Grundstaerke der Truppe verbessern",
				"[Upgrade] Ausbildungskosten reduzierung");

		//XXX: Ausgabe der aktuellen Werte, wie ein Batelion aussieht wenn sie jetz ausgebildet wird

		printFussZeile();

		std::cin >> Eingabe;
	}
		break;
	case scoutbuero:
	{
		printKopfZeile("Scoutbüro");

		std::cout << "Was möchten Sie machen? \n\n"
				<< "(" << AUSWAHL_AKTION_1	<< ") Suche nach einen guten Kämpfer starten)\n";

		printGebaeudeStats(stats,
				"[Upgrade] Verkürzen der Suchdauer",
				"[Upgrade] Bessere Kämpfer finden und anwerben(Höhere Rang)",
				"[Upgrade] Die Kosten für die Suche reduzieren");

		//XXX: Ausgabe der aktuellen Werte, wie die Suche aussieht wenn sie jetz gestartet wird

		printFussZeile();

		std::cin >> Eingabe;
	}
		break;
	case traningszentrum:
	{
		printKopfZeile("Traningszentrum");

		std::cout << "Was möchten Sie machen? \n\n"
				<< "(" << AUSWAHL_AKTION_1	<< ") Ein intensiv Traening starten\n"
				<< "(" << AUSWAHL_AKTION_2	<< ") Ein gutes grundlagen Traning starten"
				<< "(" << AUSWAHL_AKTION_3	<< ") Einmal kurz ins Gym\n";

		printGebaeudeStats(stats,
				"[Upgrade] Verkürzung der Traningsdauer",
				"[Upgrade] Die Traningsmethoden verbessern",
				"[Upgrade] Die Kosten fuer ein Traning senken");

		printFussZeile();

		std::cin >> Eingabe;
	}
		break;
	case erholungsresort:
	{
		printKopfZeile("Erholungsresort");

		std::cout << "Was möchten Sie machen? \n\n"
				<< "(" << AUSWAHL_AKTION_1	<< ") Eine Einheit zum erholen(HP und Moral) auswahlen";

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
		hilfsDialog();
	}
}

void hilfsDialog()
{
	std::cout << "Wilkommen im Hilfsmenu. \n Aktuell gibt es keine Eintrage zum Menu in dem du dich befindest, daher kann ich dir leider nicht helfen :( . ";
}
