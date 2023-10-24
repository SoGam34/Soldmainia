#include "Traningszentrum.h"

Traningszentrum::Traningszentrum(std::shared_ptr<Data> data, std::mutex& mutex) : Gebaeude(data, 16,100,1, mutex), Auswahl(data, mutex),
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

void Traningszentrum::AuswahlZuOrdnen(int Position, std::mutex& mutex)
{
	EinheitsVPosition = Position;
	leeren();
	BeginnAufgabe(mutex);
}

const std::stringstream Traningszentrum::GebaudeAktivText() const
{
	// Der Text der warend des Trainings angezeigt wird 
	std::stringstream ssText;
	ssText << "Die Einheit "<<cData->getEinheiten()[EinheitsVPosition].sName<<"\nwird gerade Trainiert\nDas Training ist\nvorausicht in "<<iVoraussichtlicheZeit<<"\nTagen abgeschlossen";
	return ssText;
}

void Traningszentrum::BeendenDerAusfuhrung()
{
	//neues Kachel Bild
	iZeitversatz = rand() % 5 + 3;		// Berechnung der Ausbildungsdauer des n�chsten Batilions 
	BerrechnungVoraussichtlicheZeit();
	
	bProzessAktiv = false;	// Auf False setzen damit nicht der andere Text ausgegeben wird von aktAusbildung
	
	std::stringstream ssText;			// Der Text der Angezeigt werden soll
	ssText << "Neue Einheit Trainieren\nDie Einheit erhalt\nErfahrungspunkte was sie\nStarker macht und\ndie Erfolgsraten in\nEinsatzen verbessert.\nDie Menge der\nErfahrungspunkte hangt von\nder Dauer ab";

	cData->getKacheln(16).neueAnzeige(ssText.str(), 200, 99, 1, 1);	// Akktualiesieren des Textes 
	//// Hinzuf�gen aller Notiger Buttens 
	cData->getKacheln(16).ButtonHinzufuegen(45, 450, 200, 30, 5, "Lange Tranings Einheit",		*cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White, cData->getKacheln(16).getGroese().x, cData->getKacheln(16).getGroese().y);
	cData->getKacheln(16).ButtonHinzufuegen(45, 350, 200, 30, 6, "Kurze Trainings Einheit", *cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White, cData->getKacheln(16).getGroese().x, cData->getKacheln(16).getGroese().y);
	cData->getKacheln(16).ButtonHinzufuegen(45, 400, 200, 30, 7, "Mittlere trainings Einheit", *cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White, cData->getKacheln(16).getGroese().x, cData->getKacheln(16).getGroese().y);
	
	cData->getAnimationen().startBenarichtigung(true, "Das Training ist beendet");

	cData->getEinheiten()[EinheitsVPosition].XPHinzufugen(iWirksamkeitsgrad* iGebaeudeEinflussZeitFaktor);
}


inline void Traningszentrum::aktualisierenInformationsText()
{
	std::stringstream ssText;
	ssText << "Sie wahlen eine\nEinheit(Batilion/EM) aus,\nwelche im Zentrum\ntraniert wird,\ndadurch wird sie\nStarker und erhalt\nKampferfahrung was ein\nVorteil in Einsatzen\nist.";
	
	cData->getKacheln(16).TextAendern(ssText.str(), 200);
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
		cData->getAnimationen().startUpgradeAnimation(3, cData->getBreite(), cData->getHohe());

		ss.str("");
		if (!bProzessAktiv)	// �berpr�ft ob ein Batilion ausgebildet wird, wenn ja wird die Anzeige und  Uhr nicht aktualiesiert da dies zu Anzeigebugs f�hrt
		{
			aktualisierenInformationsText();
			BerrechnungVoraussichtlicheZeit();
		}

		if (iWirksamkeitsgrad > 24)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nwuerde erreicht.\nSie koennen diesen\nPrarameter nicht mehr\noprimieren";
			cData->getKacheln(16).neueAnzeige(ss.str(), 350, 1, 535, 95);
		}

		else
		{
			// Ausgabe des neuen Textes
			ss << "Erhoung der Grundstaerke\nKosten: " << fUpgradeKosten[1];
			cData->getKacheln(16).TextAendern(ss.str(), 350);
		}
	}
}
