#include "Batilion_Ausbildungszentrum.h"

Batilion_Ausbildungszentrum::Batilion_Ausbildungszentrum(std::shared_ptr<Data> data, std::mutex& mutex) : Gebaeude(data, 8, 70, 10, mutex), iBatilionsgroesse(10),
fGrundstaerke(10)
{
	
}

Batilion_Ausbildungszentrum::~Batilion_Ausbildungszentrum()
{
}

unsigned const int Batilion_Ausbildungszentrum::GebaeudeAusfuhrungskosten() const
{
	return iAusfuhrungsKostenFaktor * (iVoraussichtlicheZeit + iZeitversatz);
}

const std::stringstream Batilion_Ausbildungszentrum::GebaudeAktivText() const
{
	// Der Text der warend der Ausbildung angezeigt wird 
	std::stringstream ssText;
	ssText << "Ausbildung eines neuen \nBatilions ist im Gang.\n"
		<< "Das Batilion wird aus\n" << iBatilionsgroesse << " Mitgliedern bestehen.\n"
		<< "Die Ausbildung wird in\n" << getTimerstand() << " Tagen vorausichtlich\nfertig sein.";
	return ssText;
}

void Batilion_Ausbildungszentrum::AnzahlErhohen()
{
	// Erhoht die Gesamtanzahl der Soldaten in dem Batilion und aktualiesiert die Ausgabe
	iBatilionsgroesse += 1;
	iGebaeudeEinflussZeitFaktor = iBatilionsgroesse;
	BerrechnungVoraussichtlicheZeit();
	aktualisierenInformationsText();
}

void Batilion_Ausbildungszentrum::AnzahlReduzieren()
{
	// Reduziert die Gesamtanzahl der Soldaten in dem Batilion und aktualiesiert die Ausgabe
	iBatilionsgroesse -= 1;
	iGebaeudeEinflussZeitFaktor = iBatilionsgroesse;
	BerrechnungVoraussichtlicheZeit();
	aktualisierenInformationsText();
}

void Batilion_Ausbildungszentrum::BeendenDerAusfuhrung()
{
	cData->getKacheln(8).neueAnzeige("Die Ausblidung ist\nbeendet, wie wollen\nsie das Batiliion\nnennen?", 100, 99, 1, 1);	// Akktualiesieren des Textes 

	//cData->getKacheln(8).addTextfeld(sf::Color::Black, cData->getFont(), sf::Vector2f(40, 200));
	cData->getKacheln(8).ButtonHinzufuegen(35, 350, 200, 30, 5, "Namen Bestehtigen", *cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, cData->getKacheln(8).getGroese().x, cData->getKacheln(8).getGroese().y);
	bProzessAktiv = false;	// Auf False setzen damit nicht der andere Text ausgegeben wird von aktAusbildung
	//Generierung eines Batilions
	cData->getAnimationen().startBenarichtigung(true,"Ausbildung Batilion beendet");
}

void Batilion_Ausbildungszentrum::Vorbereiten_neueAusbildung()
{
	//neues Kachel Bild
	iZeitversatz = rand() % 5 + 3;		// Berechnung der Ausbildungsdauer des n�chsten Batilions 
	BerrechnungVoraussichtlicheZeit();

	std::stringstream ssText;			// Der Text der Angezeigt werden soll
	ssText << "Neues Batilion Ausbilden\nGr��e: " << iBatilionsgroesse << "\nKampfkraft: " << iBatilionsgroesse * 10 * fGrundstaerke << "\nKosten: " << iAusfuhrungsKostenFaktor * iVoraussichtlicheZeit << "\nVorausichtlich fertig in: " << iVoraussichtlicheZeit;

	cData->getKacheln(8).neueAnzeige(ssText.str(), 200, 99, 1, 1);	// Akktualiesieren des Textes 
	// Hinzuf�gen aller Notiger Buttens 
	cData->getKacheln(8).ButtonHinzufuegen(35, 450, 200, 30, 1, "Starten",				*cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, cData->getKacheln(8).getGroese().x, cData->getKacheln(8).getGroese().y);
	cData->getKacheln(8).ButtonHinzufuegen(35, 350, 200, 30, 11, "Mehr Mitglieder",	*cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, cData->getKacheln(8).getGroese().x, cData->getKacheln(8).getGroese().y);
	cData->getKacheln(8).ButtonHinzufuegen(35, 400, 200, 30, 12, "Weniger Mitglieder", *cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, cData->getKacheln(8).getGroese().x, cData->getKacheln(8).getGroese().y);
}


inline void Batilion_Ausbildungszentrum::aktualisierenInformationsText()
{
	//Aktualieseiren der Anzeige wie das n�chste Batilion ausehen wird 
	std::stringstream ssText;
	ssText << "Neues Batilion Ausbilden\nGr��e: " << iBatilionsgroesse << "\nKampfkraft: " << iBatilionsgroesse * 10 * fGrundstaerke << "\nKosten: " << iAusfuhrungsKostenFaktor * iVoraussichtlicheZeit << "\nVorausichtlich fertig in: " << iVoraussichtlicheZeit;
	
	cData->getKacheln(8).TextAendern(ssText.str(), 200);
}

void Batilion_Ausbildungszentrum::ErhohenDerGrundstarke()
{
	if (cData->getiKontostand() > fUpgradeKosten[1] && fGrundstaerke < 25)	// �berpr�fen ob die Ausbildung bezahlt werden kann
	{
		fGrundstaerke += 1;											// Durchf�ren der Verbesserung 

		std::stringstream ssk;
		ssk << -fUpgradeKosten[1];
		cData->getAnimationen().startBenarichtigung(false, ssk.str());
		ssk.clear();

		cData->setiKontostand(cData->getiKontostand() - fUpgradeKosten[1]);			// Abziehn der Verbesserungskosten
		fUpgradeKosten[1] *= 1.6;						// Speichern der neuen Verbesserungskosten

		cData->setiKontostand(cData->getiKontostand() - fUpgradeKosten[1]);			// Abziehn der Verbesserungskosten
		//fUpgradeKosten[1]= fUpgradeKosten[1] * ((iLevel[1] < 9) ? cData->getUpgradeFaktorScoutbuero(2, 0) : (iLevel[1] < 17) ? cData->getUpgradeFaktorScoutbuero(2, 1) : cData->getUpgradeFaktorScoutbuero(2, 2)));					// Speichern der neuen Verbesserungskosten

		cData->getAnimationen().startUpgradeAnimation(3, cData->getBreite(), cData->getHohe());
		
		std::stringstream ss;
		if (!bProzessAktiv)	// �berpr�ft ob ein Batilion ausgebildet wird, wenn ja wird die Anzeige und  Uhr nicht aktualiesiert da dies zu Anzeigebugs f�hrt
		{
			aktualisierenInformationsText();
			BerrechnungVoraussichtlicheZeit();
		}

		if (fGrundstaerke > 24)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nw�rde erreicht.\nSie k�nnen diesen\nPrarameter nicht mehr\noprimieren";
			cData->getKacheln(10).neueAnzeige(ss.str(), 350, 1, 535, 95);
		}

		else
		{
			// Ausgabe des neuen Textes
			ss << "Erhoung der Grundst�rke\nKosten: " << fUpgradeKosten[1];
			cData->getKacheln(10).TextAendern(ss.str(), 350);
		}

		ss.clear();
	}
}
