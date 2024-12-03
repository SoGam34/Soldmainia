#include "Traningszentrum.h"

Traningszentrum::Traningszentrum(std::shared_ptr<Data> data)
    : Gebaeude(data, 100, 1), Auswahl(data), Wirksamkeitsgrad(1)
{
	EinheitsVPosition = 0;
}

Traningszentrum::~Traningszentrum()
{
}

unsigned const int Traningszentrum::getGebaeudeAusfuhrungskosten() const
{
	return AusfuhrungsKostenFaktor * (VoraussichtlicheZeit + Zeitversatz) *
	       Daten->getEinheiten()[EinheitsVPosition].Grosse;
}

void Traningszentrum::langeTrainingsDauer()
{
	GebaeudeEinflussZeitFaktor = 3;
	sucheNachUnverletztenEinsetzbarenEinheiten();
}

void Traningszentrum::mittlereTrainingsDauer()
{
	GebaeudeEinflussZeitFaktor = 2;
	sucheNachUnverletztenEinsetzbarenEinheiten();
}

void Traningszentrum::kurzeTraningsDauer()
{
	GebaeudeEinflussZeitFaktor = 1;
	sucheNachUnverletztenEinsetzbarenEinheiten();
}

void Traningszentrum::auswahlZuOrdnen(int Position)
{
	EinheitsVPosition = Position;
	leeren();
	beginneAufgabe();
}

const std::stringstream Traningszentrum::getGebaudeAktivText() const
{
	// Der Text der warend des Trainings angezeigt wird
	std::stringstream ssText;
	ssText << "Die Einheit "
	       << Daten->getEinheiten()[EinheitsVPosition].getName()
	       << "\nwird gerade Trainiert\nDas Training ist\nvorausicht in "
	       << VoraussichtlicheZeit << "\nTagen abgeschlossen";
	return ssText;
}

void Traningszentrum::beendenDerAusfuhrung()
{
	// neues Kachel Bild
	Zeitversatz =
	    rand() % 5 +
	    3; // Berechnung der Ausbildungsdauer des n�chsten Batillions
	berrechnungVoraussichtlicheZeit();

	ProzessAktiv = false; // Auf False setzen damit nicht der andere Text
			      // ausgegeben wird von aktAusbildung

	std::stringstream ssText; // Der Text der Angezeigt werden soll
	ssText << "Neue Einheit Trainieren\nDie Einheit "
		  "erhalt\nErfahrungspunkte was sie\nStarker macht und\ndie "
		  "Erfolgsraten in\nEinsatzen verbessert.\nDie Menge "
		  "der\nErfahrungspunkte hangt von\nder Dauer ab";

	Daten->getKacheln(16).neueAnzeige(ssText.str(), 200, 99, 1,
					  1); // Akktualiesieren des Textes
	//// Hinzuf�gen aller Notiger Buttens
	Daten->getKacheln(16).ButtonHinzufuegen(
	    45, 450, 200, 30, 5, "Lange Tranings Einheit", *Daten->getFont(),
	    sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50),
	    sf::Color::White, Data->getKacheln(16).getGroese().x,
	    Data->getKacheln(16).getGroese().y);
	Daten->getKacheln(16).ButtonHinzufuegen(
	    45, 350, 200, 30, 6, "Kurze Trainings Einheit", *Daten->getFont(),
	    sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50),
	    sf::Color::White, Data->getKacheln(16).getGroese().x,
	    Data->getKacheln(16).getGroese().y);
	Daten->getKacheln(16).ButtonHinzufuegen(
	    45, 400, 200, 30, 7, "Mittlere trainings Einheit",
	    *Daten->getFont(), sf::Color::Black, sf::Color(100, 100, 100),
	    sf::Color(50, 50, 50), sf::Color::White,
	    Data->getKacheln(16).getGroese().x,
	    Data->getKacheln(16).getGroese().y);

	// Daten->getAnimationen().startBenarichtigung(true, "Das Training ist
	// beendet");	TODO UI Animation

	Daten->getEinheiten()[EinheitsVPosition].xpHinzufugen(
	    Wirksamkeitsgrad * GebaeudeEinflussZeitFaktor);
}

inline void Traningszentrum::aktualisierenInformationsText()
{
	std::stringstream ssText;
	ssText << "Sie wahlen eine\nEinheit(Batillion/EM) aus,\nwelche im "
		  "Zentrum\ntraniert wird,\ndadurch wird sie\nStarker und "
		  "erhalt\nKampferfahrung was ein\nVorteil in Einsatzen\nist.";

	Daten->getKacheln(16).TextAendern(ssText.str(), 200);
}

void Traningszentrum::erhohenDerTraningsWirksamkeit()
{
	if (Daten->getKontostand() > UpgradeKosten[1] &&
	    Wirksamkeitsgrad <
		25) // �berpr�fen ob die Ausbildung bezahlt werden kann
	{
		Wirksamkeitsgrad += 1; // Durchf�ren der Verbesserung
		UpgradeKosten[1] *=
		    1.6; // Speichern der neuen Verbesserungskosten
		Daten->abziehnVonKontostand(
		    UpgradeKosten[1]); // Abziehn der Verbesserungskosten

		std::stringstream ss;
		ss << -UpgradeKosten[1];
		// Daten->getAnimationen().startBenarichtigung(false, ss.str());
		// TODO UI Animation
		// Daten->getAnimationen().startUpgradeAnimation(3,
		// Data->getBreite(), Data->getHohe());	TODO UI Animation

		ss.str("");
		if (!ProzessAktiv) // �berpr�ft ob ein Batillion ausgebildet
				   // wird, wenn ja wird die Anzeige und  Uhr
				   // nicht aktualiesiert da dies zu Anzeigebugs
				   // f�hrt
		{
			aktualisierenInformationsText();
			berrechnungVoraussichtlicheZeit();
		}

		if (Wirksamkeitsgrad > 24)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nwuerde erreicht.\nSie "
			      "koennen diesen\nPrarameter nicht "
			      "mehr\noprimieren";
			Daten->getKacheln(16).neueAnzeige(ss.str(), 350, 1, 535,
							  95);
		}

		else
		{
			// Ausgabe des neuen Textes
			ss << "Erhoehung der Grundstaerke\nKosten: "
			   << UpgradeKosten[1];
			Daten->getKacheln(16).TextAendern(ss.str(), 350);
		}
	}
}
