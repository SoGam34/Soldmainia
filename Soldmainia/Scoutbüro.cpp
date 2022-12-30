#include "Scoutbüro.h"

Scoutbüro::Scoutbüro() : Gebaeude(12, 1)
{
	iRangmin = 1;
	iKostenmitarbeiter = 400;
	BerrechnungVoraussichtlicheZeit();
	eRang = static_cast<Rang>(rand()%2+iRangmin);
}

Scoutbüro::Scoutbüro(Data* data) : Gebaeude(data, 12, 1)
{
	iRangmin = 1;
	iKostenmitarbeiter = 400;
	BerrechnungVoraussichtlicheZeit();
	eRang = static_cast<Rang>(rand() % 2 + iRangmin);
}

Scoutbüro::~Scoutbüro()
{
}

std::stringstream Scoutbüro::ProzessText()
{
	 std::stringstream ssText;
	 ssText << "Die Mitarbeiter des\nScoutbüros suchen intensiv\nnach einem Geeignetem\nMitglied. Die Suche\ndauert voraussichtlich\nnoch " << getTimerstand();
	 return ssText;
}

void Scoutbüro::EndeProzess()
{
	std::stringstream ssText;
	ssText << "Starke:Test\nAffinität: Test\nProzentualer Anteil: Test";
	cData->getKacheln(12).neuesBild(ssText.str(), 160, 99, 1, 1);
	cData->getKacheln(12).addButten(35, 400, 200, 30, 5, "Annehmen", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
	cData->getKacheln(12).addButten(35, 450, 200, 30, 6, "Ablehnen", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);

	
	bProzessAktiv = false;	// Auf False setzen damit nicht der andere Text ausgegeben wird von aktAusbildung
	cData->getAnimationen().startBenarichtigung(true, "Suche erfolgreich Abgeschlossen");
	ssText.clear();
}

void Scoutbüro::Annehmen()
{
	// EM dauerhaft in Data speichern
	cData->getKacheln(12).neuesBild("Error in Annehmen", 160, 99, 1, 1);
	aktstd();
	cData->getKacheln(12).addButten(35, 450, 200, 30, 1, "Starten", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
	cData->getAnimationen().startBenarichtigung(true, "EM Angenomen");
}

void Scoutbüro::Ablehnen()
{
	//EM = nullptr
	cData->getKacheln(12).neuesBild("Error in Ablehnen", 160, 99, 1, 1);
	aktstd();
	cData->getKacheln(12).addButten(35, 450, 200, 30, 1, "Starten", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
	cData->getAnimationen().startBenarichtigung(false, "EM Abgelehnt");
	bProzessAktiv = false;
}

void Scoutbüro::UpgradeRang()
{
	if (cData->getiKontostand() > cData->getfUpgradeKosten(1, 1) && iRangmin<6)								// überprüfen ob die Ausbildung bezahlt werden kann
	{
		iRangmin++;																							// Durchfüren der Verbesserung 

		std::stringstream ssk;
		ssk << -(cData->getfUpgradeKosten(1, 1));
		cData->getAnimationen().startBenarichtigung(false, ssk.str());
		ssk.clear();

		cData->setiKontostand(cData->getiKontostand() - cData->getfUpgradeKosten(1, 1));					// Abziehn der Verbesserungskosten
		cData->setfUpgradeKosten(1, 1, cData->getfUpgradeKosten(1, 1) * 1.6);								// Speichern der neuen Verbesserungskosten

		cData->getAnimationen().startUpgradeAnimation(3);
		eRang = static_cast<Rang>(rand() % 2 + iRangmin);
		cData->setiZeitFaktor(eRang, 1);
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
		std::stringstream ss;
		if (!bProzessAktiv)	// überprüft ob ein Batilion ausgebildet wird, wenn ja wird die Anzeige und  Uhr nicht aktualiesiert da dies zu Anzeigebugs führt
		{
			BerrechnungVoraussichtlicheZeit();
			aktstd();
		}

		if (iRangmin == 6)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nwürde erreicht.\nSie können diesen\nPrarameter nicht mehr\noprimieren";
			cData->getKacheln(14).neuesBild(ss.str(), 350, 1, 535, 95);
		}

		else
		{
			// Ausgabe des neuen Textes
			ss << "Das Scoutbüro\nfindet Einzelkampfer die\neinen höheren Rang\nund Potenzial habne\nKosten: " << cData->getfUpgradeKosten(1, 1);
			cData->getKacheln(14).changeText(ss.str(), 320);
		}

		ss.clear();
	}	
}

void Scoutbüro::aktstd()
{
	std::stringstream ssText;
	ssText << "Einselkämpfer Rekutieren\n(EM)\nEin EM bekommt\nein Teil der Finanzellen\nBehlohnung und hat\neine Affinität.\nDie Affinität erlaubt\ndie Ausstatung spezieller\nWaffen und bringt\nVorteile bei bestimmten\nAuftragen."; //\nSuchkosten: " << eRang * iKostenmitarbeiter * iVoraussichtlicheZeit << "\nVoraussichtliche dauer: " << iVoraussichtlicheZeit;
	cData->getKacheln(12).changeText(ssText.str(), 200);
	ssText.clear();
}