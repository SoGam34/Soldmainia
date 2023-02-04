#include "Traningszentrum.h"

Traningszentrum::Traningszentrum(Data*data) : Gebaeude(data, 16,100,1), Auswahl(data),
iWirksamkeitsgrad(1)
{
}

Traningszentrum::~Traningszentrum()
{
}


unsigned const int Traningszentrum::GebaeudeAusfuhrungskosten() const
{
	return iAusfuhrungsKostenFaktor *(iVoraussichtlicheZeit+iZeitversatz)*cData->getEinheiten()[EinheitsVPosition].Grosse;
}

void Traningszentrum::LangeTrainingsDauer()
{
	iGebaeudeEinflussZeitFaktor = 3;
	SucheEinsetzbare_UND_GesundeEinheiten();
}

void Traningszentrum::MittlereTrainingsDauer()
{
	iGebaeudeEinflussZeitFaktor = 2;
	SucheEinsetzbare_UND_GesundeEinheiten();
}

void Traningszentrum::KurzeTraningsDauer()
{
	iGebaeudeEinflussZeitFaktor = 1;
	SucheEinsetzbare_UND_GesundeEinheiten();
}

void Traningszentrum::AuswahlZuOrdnen(int Position)
{
	EinheitsVPosition = Position;
	leeren();
	BeginnAufgabe();
}

const std::stringstream Traningszentrum::GebaudeAktivText() const
{
	// Der Text der warend des Trainings angezeigt wird 
	std::stringstream ssText;
	ssText << "Die Einheit "<<cData->getEinheiten()[EinheitsVPosition].sName<<"\nwird gerade Trainiert\nDas Training ist\nvorausicht in "<<iVoraussichtlicheZeit<<"\nTagen abgeschlo�en";
	return ssText;
}

void Traningszentrum::BeendenDerAusfuhrung()
{
	//neues Kachel Bild
	iZeitversatz = rand() % 5 + 3;		// Berechnung der Ausbildungsdauer des n�chsten Batilions 
	BerrechnungVoraussichtlicheZeit();
	
	bProzessAktiv = false;	// Auf False setzen damit nicht der andere Text ausgegeben wird von aktAusbildung
	
	std::stringstream ssText;			// Der Text der Angezeigt werden soll
	ssText << "Neue Einheit Trainieren\nDie Einheit erhalt\nErfahrungspunkte was sie\nStarker macht und\ndie Erfolgsraten in\nEinsatzen verbessert.\nDei Menge der\nErfahrungspunkte hangt von\nder Dauer ab";

	cData->getKacheln(16).neuesBild(ssText.str(), 200, 99, 1, 1);	// Akktualiesieren des Textes 
	//// Hinzuf�gen aller Notiger Buttens 
	cData->getKacheln(16).addButten(45, 450, 200, 30, 5, "Lange Tranings Einheit", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
	cData->getKacheln(16).addButten(45, 350, 200, 30, 6, "Kurze Trainings Einheit", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
	cData->getKacheln(16).addButten(45, 400, 200, 30, 7, "Mittlere trainings Einheit", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
	
	cData->getAnimationen().startBenarichtigung(true, "Das Training ist beendet");

	cData->getEinheiten()[EinheitsVPosition].XPHinzufugen(iWirksamkeitsgrad* iGebaeudeEinflussZeitFaktor);
}


inline void Traningszentrum::aktualisierenInformationsText()
{
	std::stringstream ssText;
	ssText << "Sie wahlen eine\nEinheit(Batilion/EM) aus,\nwelche im Zentrum\ntraniert wird,\ndadurch wird sie\nStarker und erhalt\nKampferfahrung was ein\nVorteil in Einsatzen\nist.";
	cData->getKacheln(16).changeText(ssText.str(), 200);
}

void Traningszentrum::ErhohenDerTraningsWirksamkeit()
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

		if (iWirksamkeitsgrad > 24)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nw�rde erreicht.\nSie k�nnen diesen\nPrarameter nicht mehr\noprimieren";
			cData->getKacheln(16).neuesBild(ss.str(), 350, 1, 535, 95);
		}

		else
		{
			// Ausgabe des neuen Textes
			ss << "Erhoung der Grundst�rke\nKosten: " << fUpgradeKosten[1];
			cData->getKacheln(16).changeText(ss.str(), 350);
		}
	}
}