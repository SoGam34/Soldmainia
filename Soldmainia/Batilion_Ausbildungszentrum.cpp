#include "Batilion_Ausbildungszentrum.h"

Batilion_Ausbildungszentrum::Batilion_Ausbildungszentrum(Data* data) : Gebaeude(data, 8, 70, 10)
{
	iBekanntheit = 1;
	iBatilonsgr��e = 10;
	iKostenproKopf = 70;
	fGrundst�rke = 10;
}

Batilion_Ausbildungszentrum::~Batilion_Ausbildungszentrum()
{
}

std::stringstream Batilion_Ausbildungszentrum::ProzessText()
{
	// Der Text der warend der Ausbildung angezeigt wird 
	std::stringstream ssText;
	ssText << "Ausbildung eines neuen \nBatilions ist im Gang.\n"
		<< "Das Batilion wird aus\n" <<iBatilonsgr��e << " Mitgliedern bestehen.\n"
		<< "Die Ausbildung wird in\n" << getTimerstand() << " Tagen vorausichtlich\nfertig sein.";
	return ssText;
}

int Batilion_Ausbildungszentrum::ProzessKosten()
{
	return iKostenproKopf * (iVoraussichtlicheZeit + iZeitversatz);
}

void Batilion_Ausbildungszentrum::EndeProzess()
{
	cData->getKacheln(8).neuesBild("Die Ausblidung ist\nbeendet, wie wollen\nsie das Batiliion\nnennen?", 100, 99, 1, 1);	// Akktualiesieren des Textes 

	//cData->getKacheln(8).addTextfeld(sf::Color::Black, cData->getFont(), sf::Vector2f(40, 200));
	cData->getKacheln(8).addButten(35, 350, 200, 30, 5, "Namen Bestehtigen", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White);
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
	ssText << "Neues Batilion Ausbilden\nGr��e: " << iBatilonsgr��e << "\nKampfkraft: " << iBatilonsgr��e * 10 * fGrundst�rke << "\nKosten: " << iKostenproKopf * iVoraussichtlicheZeit << "\nVorausichtlich fertig in: " << iVoraussichtlicheZeit;

	cData->getKacheln(8).neuesBild(ssText.str(), 200, 99, 1, 1);	// Akktualiesieren des Textes 
	// Hinzuf�gen aller Notiger Buttens 
	cData->getKacheln(8).addButten(35, 450, 200, 30, 1, "Starten", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White);
	cData->getKacheln(8).addButten(35, 350, 200, 30, 11, "Mehr Mitglieder", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White);
	cData->getKacheln(8).addButten(35, 400, 200, 30, 12, "Weniger Mitglieder", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White);
}


void Batilion_Ausbildungszentrum::aktstd()
{
	//Aktualieseiren der Anzeige wie das n�chste Batilion ausehen wird 
	std::stringstream ssText;
	ssText << "Neues Batilion Ausbilden\nGr��e: " << iBatilonsgr��e << "\nKampfkraft: " << iBatilonsgr��e * 10 * fGrundst�rke << "\nKosten: " << iKostenproKopf * iVoraussichtlicheZeit << "\nVorausichtlich fertig in: " << iVoraussichtlicheZeit;
	cData->getKacheln(8).changeText(ssText.str(), 200);
	ssText.clear();
}

void Batilion_Ausbildungszentrum::AnzahlErhohen()
{
	// Erhoht die Gesamtanzahl der Soldaten in dem Batilion und aktualiesiert die Ausgabe
	iBatilonsgr��e += 1;
	iZeitFaktor = iBatilonsgr��e;
	BerrechnungVoraussichtlicheZeit();
	aktstd();
}

void Batilion_Ausbildungszentrum::AnzahlReduzieren()
{
	// Reduziert die Gesamtanzahl der Soldaten in dem Batilion und aktualiesiert die Ausgabe
	iBatilonsgr��e -= 1;
	iZeitFaktor = iBatilonsgr��e;
	BerrechnungVoraussichtlicheZeit();
	aktstd();
}

void Batilion_Ausbildungszentrum::UpgradeGrundstarke()
{
	if (cData->getiKontostand() > fUpgradeKosten[1] && fGrundst�rke < 25)	// �berpr�fen ob die Ausbildung bezahlt werden kann
	{
		fGrundst�rke += 1;											// Durchf�ren der Verbesserung 

		std::stringstream ssk;
		ssk << -fUpgradeKosten[1];
		cData->getAnimationen().startBenarichtigung(false, ssk.str());
		ssk.clear();

		cData->setiKontostand(cData->getiKontostand() - fUpgradeKosten[1]);			// Abziehn der Verbesserungskosten
		fUpgradeKosten[1] *= 1.6;						// Speichern der neuen Verbesserungskosten

		cData->getAnimationen().startUpgradeAnimation(3);
		
		std::stringstream ss;
		if (!bProzessAktiv)	// �berpr�ft ob ein Batilion ausgebildet wird, wenn ja wird die Anzeige und  Uhr nicht aktualiesiert da dies zu Anzeigebugs f�hrt
		{
			aktstd();
			BerrechnungVoraussichtlicheZeit();
		}

		if (fGrundst�rke > 24)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nw�rde erreicht.\nSie k�nnen diesen\nPrarameter nicht mehr\noprimieren";
			cData->getKacheln(10).neuesBild(ss.str(), 350, 1, 535, 95);
		}

		else
		{
			// Ausgabe des neuen Textes
			ss << "Erhoung der Grundst�rke\nKosten: " << fUpgradeKosten[1];
			cData->getKacheln(10).changeText(ss.str(), 350);
		}

		ss.clear();
	}
}