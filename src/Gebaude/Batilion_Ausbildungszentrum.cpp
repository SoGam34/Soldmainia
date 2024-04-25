#include "Batilion_Ausbildungszentrum.h"

Batillion_Ausbildungszentrum::Batillion_Ausbildungszentrum(std::shared_ptr<Data> data, std::mutex& mutex) : Gebaeude(data, 8, 70, 10, mutex), iBatillionsgroesse(10),
fGrundstaerke(10)
{
	
}

Batillion_Ausbildungszentrum::~Batillion_Ausbildungszentrum()
{
}

unsigned const int Batillion_Ausbildungszentrum::GebaeudeAusfuhrungskosten() const
{
	return iAusfuhrungsKostenFaktor * (iVoraussichtlicheZeit + iZeitversatz);
}

const std::stringstream Batillion_Ausbildungszentrum::GebaudeAktivText() const
{
	// Der Text der warend der Ausbildung angezeigt wird 
	std::stringstream ssText;
	ssText << "Ausbildung eines neuen \nBatillions ist im Gang.\n"
		<< "Das Batillion wird aus\n" << iBatillionsgroesse << " Mitgliedern bestehen.\n"
		<< "Die Ausbildung wird in\n" << getTimerstand() << " Tagen vorausichtlich\nfertig sein.";
	return ssText;
}

void Batillion_Ausbildungszentrum::AnzahlErhohen()
{
	// Erhoht die Gesamtanzahl der Soldaten in dem Batillion und aktualiesiert die Ausgabe
	iBatillionsgroesse += 1;
	iGebaeudeEinflussZeitFaktor = iBatillionsgroesse;
	BerrechnungVoraussichtlicheZeit();
	aktualisierenInformationsText();
}

void Batillion_Ausbildungszentrum::AnzahlReduzieren()
{
	// Reduziert die Gesamtanzahl der Soldaten in dem Batillion und aktualiesiert die Ausgabe
	iBatillionsgroesse -= 1;
	iGebaeudeEinflussZeitFaktor = iBatillionsgroesse;
	BerrechnungVoraussichtlicheZeit();
	aktualisierenInformationsText();
}

void Batillion_Ausbildungszentrum::BeendenDerAusfuhrung()
{
	cData->getKacheln(8).neueAnzeige("Die Ausblidung ist\nbeendet, wie wollen\nsie das Batiliion\nnennen?", 100, 99, 1, 1);	// Akktualiesieren des Textes 

	//cData->getKacheln(8).addTextfeld(sf::Color::Black, cData->getFont(), sf::Vector2f(40, 200));
	cData->getKacheln(8).ButtonHinzufuegen(35, 350, 200, 30, 5, "Namen Bestehtigen", *cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, cData->getKacheln(8).getGroese().x, cData->getKacheln(8).getGroese().y);
	bProzessAktiv = false;	// Auf False setzen damit nicht der andere Text ausgegeben wird von aktAusbildung
	//Generierung eines Batillions
	cData->getAnimationen().startBenarichtigung(true,"Ausbildung Batillion beendet");
}

void Batillion_Ausbildungszentrum::Vorbereiten_neueAusbildung()
{
	//neues Kachel Bild
	iZeitversatz = rand() % 5 + 3;		// Berechnung der Ausbildungsdauer des n�chsten Batillions 
	BerrechnungVoraussichtlicheZeit();

	std::stringstream ssText;			// Der Text der Angezeigt werden soll
	ssText << "Neues Batillion ausbilden\nGroesse: " << iBatillionsgroesse << "\nKampfkraft: " << iBatillionsgroesse * 10 * fGrundstaerke << "\nKosten: " << iAusfuhrungsKostenFaktor * iVoraussichtlicheZeit << "\nVoraussichtlich fertig in: " << iVoraussichtlicheZeit;

	cData->getKacheln(8).neueAnzeige(ssText.str(), 200, 99, 1, 1);	// Akktualiesieren des Textes 
	// Hinzuf�gen aller Notiger Buttens 
	cData->getKacheln(8).ButtonHinzufuegen(35, 450, 200, 30, 1, "Starten",				*cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, cData->getKacheln(8).getGroese().x, cData->getKacheln(8).getGroese().y);
	cData->getKacheln(8).ButtonHinzufuegen(35, 350, 200, 30, 11, "Mehr Mitglieder",	*cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, cData->getKacheln(8).getGroese().x, cData->getKacheln(8).getGroese().y);
	cData->getKacheln(8).ButtonHinzufuegen(35, 400, 200, 30, 12, "Weniger Mitglieder", *cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, cData->getKacheln(8).getGroese().x, cData->getKacheln(8).getGroese().y);
}


inline void Batillion_Ausbildungszentrum::aktualisierenInformationsText()
{
	//Aktualieseiren der Anzeige wie das n�chste Batillion ausehen wird 
	std::stringstream ssText;
	ssText << "Neues Batillion ausbilden\nGroesse: " << iBatillionsgroesse << "\nKampfkraft: " << iBatillionsgroesse * 10 * fGrundstaerke << "\nKosten: " << iAusfuhrungsKostenFaktor * iVoraussichtlicheZeit << "\nVoraussichtlich fertig in: " << iVoraussichtlicheZeit;
	
	cData->getKacheln(8).TextAendern(ssText.str(), 200);
}

void Batillion_Ausbildungszentrum::ErhohenDerGrundstarke()
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
		if (!bProzessAktiv)	// �berpr�ft ob ein Batillion ausgebildet wird, wenn ja wird die Anzeige und  Uhr nicht aktualiesiert da dies zu Anzeigebugs f�hrt
		{
			aktualisierenInformationsText();
			BerrechnungVoraussichtlicheZeit();
		}

		if (fGrundstaerke > 24)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nwuerde erreicht.\nSie koennen diesen\nPrarameter nicht mehr\noprimieren";
			cData->getKacheln(10).neueAnzeige(ss.str(), 350, 1, 535, 95);
		}

		else
		{
			// Ausgabe des neuen Textes
			ss << "Erhoehung der Grundstaerke\nKosten: " << fUpgradeKosten[1];
			cData->getKacheln(10).TextAendern(ss.str(), 350);
		}

		ss.clear();
	}
}
