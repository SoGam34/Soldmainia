#include "Erholungsresort.h"

Erholungsresort::Erholungsresort(std::shared_ptr<Data> data) : Gebaeude(data, 100, 1), Auswahl(data),
Wirksamkeitsgrad(1)
{
}

Erholungsresort::~Erholungsresort()
{
}

unsigned const int Erholungsresort::GebaeudeAusfuhrungskosten() const
{
	return AusfuhrungsKostenFaktor * (VoraussichtlicheZeit + Zeitversatz) * Daten->getEinheiten()[EinheitsVPosition].Grosse;
}

void Erholungsresort::AuswahlZuOrdnen(int Position)
{
	EinheitsVPosition = Position;
	leeren();
	BeginnAufgabe();
}

const std::stringstream Erholungsresort::GebaudeAktivText() const
{
	// Der Text der warend des Trainings angezeigt wird 
	std::stringstream ssText;
	ssText << "Die Einheit " << Daten->getEinheiten()[EinheitsVPosition].sName << "\nwird gerade Versorgen\nDie Versorgen ist\nvorausicht in " << VoraussichtlicheZeit << "\nTagen abgeschlosen";
	return ssText;
}

void Erholungsresort::BeendenDerAusfuhrung()
{
	//neues Kachel Bild
	Zeitversatz = rand() % 5 + 3;		// Berechnung der Ausbildungsdauer des n�chsten Batillions
	BerrechnungVoraussichtlicheZeit();

	ProzessAktiv = false;	// Auf False setzen damit nicht der andere Text ausgegeben wird von aktAusbildung

	std::stringstream ssText;			// Der Text der Angezeigt werden soll
	ssText << "Neue Einheit Versorgen.\nDie Einheit regeneriert\nihre Moral und\nHP was\ndie Erfolgsraten und\nUberlebenschance in\nEinsatzen verbessert.";

	Daten->getKacheln(24).neueAnzeige(ssText.str(), 200, 99, 1, 1);	// Akktualiesieren des Textes
	//// Hinzuf�gen aller Notiger Buttens 
	Daten->getKacheln(24).ButtonHinzufuegen(45, 450, 200, 30, 5, "Erholung starten", *Daten->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White, Data->getKacheln(24).getGroese().x, Data->getKacheln(24).getGroese().y);
	
	//Daten->getAnimationen().startBenarichtigung(true, "Die Einheit ist vollstandig regeneriert");	TODO UI Animation

	Daten->getEinheiten()[EinheitsVPosition].XPHinzufugen(Wirksamkeitsgrad * GebaeudeEinflussZeitFaktor);
}


inline void Erholungsresort::aktualisierenInformationsText()
{
	std::stringstream ssText;
	ssText << "Sie wahlen eine\nEinheit(Batillion/EM) aus,\nwelche sich dann\nVersorgt wird,\ndadurch steigen die\nErfolgsraten und\nUberlebenschance in\nEinsatzen verbessert.";
	
	Daten->getKacheln(24).TextAendern(ssText.str(), 200);
}

void Erholungsresort::ErhohenDerTraningsWirksamkeit()
{
	if (Daten->getKontostand() > UpgradeKosten[1] && Wirksamkeitsgrad < 25)	// �berpr�fen ob die Ausbildung bezahlt werden kann
	{
		Wirksamkeitsgrad += 1;												// Durchf�ren der Verbesserung
		UpgradeKosten[1] *= 1.6;											// Speichern der neuen Verbesserungskosten
		Daten->setKontostand(Daten->getKontostand() - UpgradeKosten[1]); // Abziehn der Verbesserungskosten

		std::stringstream ss;
		ss << -UpgradeKosten[1];
		//Daten->getAnimationen().startBenarichtigung(false, ss.str());	TODO UI Animation
		//cData->getAnimationen().startUpgradeAnimation(3);

		ss.str("");
		if (!ProzessAktiv)	// �berpr�ft ob ein Batillion ausgebildet wird, wenn ja wird die Anzeige und  Uhr nicht aktualiesiert da dies zu Anzeigebugs f�hrt
		{
			aktualisierenInformationsText();
			BerrechnungVoraussichtlicheZeit();
		}

		if (Wirksamkeitsgrad > 26)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nwuerde erreicht.\nSie koennen diesen\nPrarameter nicht mehr\noprimieren";
			Daten->getKacheln(26).neueAnzeige(ss.str(), 350, 1, 535, 95);
		}

		else
		{
			// Ausgabe des neuen Textes
			ss << "Erhoehung der Grundstaerke\nKosten: " << UpgradeKosten[1];
			Daten->getKacheln(26).TextAendern(ss.str(), 350);
		}
	}
}
