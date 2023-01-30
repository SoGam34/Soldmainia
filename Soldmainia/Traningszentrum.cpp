#include "Traningszentrum.h"

Traningszentrum::Traningszentrum(Data*data) : Gebaeude(data, 16,100,1), Auswahl(data), iWirksamkeitsgrad(1)
{
}

Traningszentrum::~Traningszentrum()
{
}


unsigned const int GebaeudeAusfuhrungskosten() const
{
	return iKostenFaktor*(iVoraussichtlicheZeit+iZeitversatz)*cData->getEinheiten()[sName].Gro�e;
}



void Traningszentrum::LangeTrainingsDauer()
{
	iZeitFaktor = 3;
	cTraingzentrum->SucheEinsetzbare_UND_GesundeEinheiten();
}

void Traningszentrum::MittlereTrainingsDauer()
{
	iZeitFaktor = 2;
	cTraingzentrum->SucheEinsetzbare_UND_GesundeEinheiten();
}

void Traningszentrum::KurzeTraningsDauer()
{
	iZeitFaktor = 1;
	cTraingzentrum->SucheEinsetzbare_UND_GesundeEinheiten();
}

void Traningszentrum::AuswahlZuOrdnen(std::string Name)
{
	sName = Name;
	StartProzess();
}

const std::stringstream GebaudeAktivText() const
{
	// Der Text der warend des Trainings angezeigt wird 
	std::stringstream ssText;
	ssText << "Die Einheit "<<sName<<"\nwird gerade Trainiert\nDas Training ist\nvorausicht in "<<iVoraussichtlicheZeit<<"\nTagen abgeschlo�en";
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
	cData->getKacheln(16).addButten(35, 450, 200, 30, 5, "Lange Tranings Einheit", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
	cData->getKacheln(16).addButten(35, 350, 200, 30, 6, "Kurze Trainings Einheit", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
	cData->getKacheln(16).addButten(35, 400, 200, 30, 7, "Mittlere trainings Einheit", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
	
	cData->getAnimationen().startBenarichtigung(true, "Das Training ist beendet, die Einheit ist jetzt wieder Einsatzbereit");

	cData->getEinheiten()[sName].XPhinzufugen(iWirksamkeitsgrad*iZeitFaktor);	
}


inline void aktualisierenInformationsText()
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
			aktstd();
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
