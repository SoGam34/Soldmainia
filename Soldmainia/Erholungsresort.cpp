#include "Erholungsresort.h"

Erholungsresort::Erholungsresort(Data* data) : Gebaeude(data, 24, 100, 1), Auswahl(data),
iWirksamkeitsgrad(1)
{
}

Erholungsresort::~Erholungsresort()
{
}

unsigned const int Erholungsresort::GebaeudeAusfuhrungskosten() const
{
	return iAusfuhrungsKostenFaktor * (iVoraussichtlicheZeit + iZeitversatz) * cData->getEinheiten()[EinheitsVPosition].Grosse;
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
	ssText << "Die Einheit " << cData->getEinheiten()[EinheitsVPosition].sName << "\nwird gerade Versorgen\nDie Versorgen ist\nvorausicht in " << iVoraussichtlicheZeit << "\nTagen abgeschlosen";
	return ssText;
}

void Erholungsresort::BeendenDerAusfuhrung()
{
	//neues Kachel Bild
	iZeitversatz = rand() % 5 + 3;		// Berechnung der Ausbildungsdauer des n�chsten Batilions 
	BerrechnungVoraussichtlicheZeit();

	bProzessAktiv = false;	// Auf False setzen damit nicht der andere Text ausgegeben wird von aktAusbildung

	std::stringstream ssText;			// Der Text der Angezeigt werden soll
	ssText << "Neue Einheit Versorgen.\nDie Einheit regeneriert\nihre Moral und\nHP was\ndie Erfolgsraten und\nUberlebenschance in\nEinsatzen verbessert.";

	cData->getKacheln(24).neuesBild(ssText.str(), 200, 99, 1, 1);	// Akktualiesieren des Textes 
	//// Hinzuf�gen aller Notiger Buttens 
	cData->getKacheln(24).addButten(45, 450, 200, 30, 5, "Erholung starten", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
	
	cData->getAnimationen().startBenarichtigung(true, "Die Einheit ist vollstandig regeneriert");

	cData->getEinheiten()[EinheitsVPosition].XPHinzufugen(iWirksamkeitsgrad * iGebaeudeEinflussZeitFaktor);
}


inline void Erholungsresort::aktualisierenInformationsText()
{
	std::stringstream ssText;
	ssText << "Sie wahlen eine\nEinheit(Batilion/EM) aus,\nwelche sich dann\nVersorgt wird,\ndadurch steigen die\nErfolgsraten und\nUberlebenschance in\nEinsatzen verbessert.";
	cData->getKacheln(24).changeText(ssText.str(), 200);
}

void Erholungsresort::ErhohenDerTraningsWirksamkeit()
{
	if (cData->getiKontostand() > fUpgradeKosten[1] && iWirksamkeitsgrad < 25)	// �berpr�fen ob die Ausbildung bezahlt werden kann
	{
		iWirksamkeitsgrad += 1;												// Durchf�ren der Verbesserung 
		fUpgradeKosten[1] *= 1.6;											// Speichern der neuen Verbesserungskosten
		cData->setiKontostand(cData->getiKontostand() - fUpgradeKosten[1]); // Abziehn der Verbesserungskosten

		std::stringstream ss;
		ss << -fUpgradeKosten[1];
		cData->getAnimationen().startBenarichtigung(false, ss.str());
		cData->getAnimationen().startUpgradeAnimation(3);

		ss.str("");
		if (!bProzessAktiv)	// �berpr�ft ob ein Batilion ausgebildet wird, wenn ja wird die Anzeige und  Uhr nicht aktualiesiert da dies zu Anzeigebugs f�hrt
		{
			aktualisierenInformationsText();
			BerrechnungVoraussichtlicheZeit();
		}

		if (iWirksamkeitsgrad > 26)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nw�rde erreicht.\nSie k�nnen diesen\nPrarameter nicht mehr\noprimieren";
			cData->getKacheln(26).neuesBild(ss.str(), 350, 1, 535, 95);
		}

		else
		{
			// Ausgabe des neuen Textes
			ss << "Erhoung der Grundst�rke\nKosten: " << fUpgradeKosten[1];
			cData->getKacheln(26).changeText(ss.str(), 350);
		}
	}
}
