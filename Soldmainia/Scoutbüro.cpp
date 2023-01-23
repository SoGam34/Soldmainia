#include "Scoutb�ro.h"

Scoutb�ro::Scoutb�ro(Data* data) : Gebaeude(data, 12, 400, 1)
{
	iRangmin = 1;
	iKostenmitarbeiter = 400;
	BerrechnungVoraussichtlicheZeit();
	eRang = static_cast<Rang>(rand() % 2 + iRangmin);
}

Scoutb�ro::~Scoutb�ro()
{
}

std::stringstream Scoutb�ro::ProzessText()
{
	 std::stringstream ssText;
	 ssText << "Die Mitarbeiter des\nScoutb�ros suchen intensiv\nnach einem Geeignetem\nMitglied. Die Suche\ndauert voraussichtlich\nnoch " << getTimerstand();
	 return ssText;
}

int Scoutb�ro::ProzessKosten()
{
	return (eRang * iKostenmitarbeiter * (iVoraussichtlicheZeit + iZeitversatz));
}

void Scoutb�ro::EndeProzess()
{
	std::stringstream ssText;
	ssText << "Starke:Test\nAffinit�t: Test\nProzentualer Anteil: Test";
	cData->getKacheln(12).neuesBild(ssText.str(), 160, 99, 1, 1);
	cData->getKacheln(12).addButten(35, 400, 200, 30, 5, "Annehmen", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
	cData->getKacheln(12).addButten(35, 450, 200, 30, 6, "Ablehnen", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);

	
	bProzessAktiv = false;	// Auf False setzen damit nicht der andere Text ausgegeben wird von aktAusbildung
	cData->getAnimationen().startBenarichtigung(true, "Suche erfolgreich Abgeschlossen");
}

void Scoutb�ro::Annehmen()
{
	// EM dauerhaft in Data speichern
	cData->getKacheln(12).neuesBild("Error in Annehmen", 160, 99, 1, 1);
	aktstd();
	cData->getKacheln(12).addButten(35, 450, 200, 30, 1, "Starten", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
	cData->getAnimationen().startBenarichtigung(true, "EM Angenomen");
}

void Scoutb�ro::Ablehnen()
{
	//EM = nullptr
	cData->getKacheln(12).neuesBild("Error in Ablehnen", 160, 99, 1, 1);
	aktstd();
	cData->getKacheln(12).addButten(35, 450, 200, 30, 1, "Starten", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
	cData->getAnimationen().startBenarichtigung(false, "EM Abgelehnt");
	bProzessAktiv = false;
}

void Scoutb�ro::UpgradeRang()
{
	if (cData->getiKontostand() > fUpgradeKosten[1] && iRangmin<6)								// �berpr�fen ob die Ausbildung bezahlt werden kann
	{
		iRangmin++;																							// Durchf�ren der Verbesserung 
		fUpgradeKosten[1] *= 1.6;								// Speichern der neuen Verbesserungskosten
		std::stringstream ss;
		ss << -fUpgradeKosten[1];
		eRang = static_cast<Rang>(rand() % 2 + iRangmin);
		iZeitFaktor=eRang;
		
		cData->setiKontostand(cData->getiKontostand() - fUpgradeKosten[1]);					// Abziehn der Verbesserungskosten
		cData->getAnimationen().startBenarichtigung(false, ss.str());
		cData->getAnimationen().startUpgradeAnimation(3);

		
		//Erzeugen eines EM Objektes
		switch (eRang)
		{
		case S:
		{
			iZeitversatz = rand() % 20 + 7;
			BerrechnungVoraussichtlicheZeit();
		}break;
		case A:
		{
			iZeitversatz = rand() % 20 + 9;
			BerrechnungVoraussichtlicheZeit();
		}break;
		case B:
		{
			iZeitversatz = rand() % 20 + 11;
			BerrechnungVoraussichtlicheZeit();
		}break;
		case C:
		{
			iZeitversatz = rand() % 20 + 13;
			BerrechnungVoraussichtlicheZeit();
		}break;
		case D:
		{
			iZeitversatz = rand() % 20 + 15;
			BerrechnungVoraussichtlicheZeit();
		}break;
		case E:
		{
			iZeitversatz = rand() % 20 + 17;
			BerrechnungVoraussichtlicheZeit();
		}break;
		case F:
		{
			iZeitversatz = rand() % 20 + 19;
			BerrechnungVoraussichtlicheZeit();
		}break;
		}

		ss.str("");
		if (!bProzessAktiv)	// �berpr�ft ob ein Batilion ausgebildet wird, wenn ja wird die Anzeige und  Uhr nicht aktualiesiert da dies zu Anzeigebugs f�hrt
		{
			BerrechnungVoraussichtlicheZeit();
			aktstd();
		}

		if (iRangmin == 6)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nw�rde erreicht.\nSie k�nnen diesen\nPrarameter nicht mehr\noprimieren";
			cData->getKacheln(14).neuesBild(ss.str(), 350, 1, 535, 95);
		}

		else
		{
			// Ausgabe des neuen Textes
			ss << "Das Scoutb�ro\nfindet Einzelkampfer die\neinen h�heren Rang\nund Potenzial habne\nKosten: " << fUpgradeKosten[1];
			cData->getKacheln(14).changeText(ss.str(), 320);
		}
	}	
}

void Scoutb�ro::aktstd()
{
	std::stringstream ssText;
	ssText << "Einselk�mpfer Rekutieren\n(EM)\nEin EM bekommt\nein Teil der Finanzellen\nBehlohnung und hat\neine Affinit�t.\nDie Affinit�t erlaubt\ndie Ausstatung spezieller\nWaffen und bringt\nVorteile bei bestimmten\nAuftragen."; //\nSuchkosten: " << eRang * iKostenmitarbeiter * iVoraussichtlicheZeit << "\nVoraussichtliche dauer: " << iVoraussichtlicheZeit;
	cData->getKacheln(12).changeText(ssText.str(), 200);
}