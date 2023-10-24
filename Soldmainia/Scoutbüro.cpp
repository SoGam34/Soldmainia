#include "Scoutbuero.h"

Scoutbuero::Scoutbuero(std::shared_ptr<Data> data, std::mutex& mutex) : Gebaeude(data, 12, 400, 1, mutex), iRangmin(1)
{
	eRang = static_cast<Rang>(rand() % 2 + iRangmin);
	//iLevel[0] = iLevel[1] = iLevel[2] = 0;
}

Scoutbuero::~Scoutbuero()
{
}

unsigned const int Scoutbuero::GebaeudeAusfuhrungskosten() const
{
	return (eRang * iAusfuhrungsKostenFaktor * (iVoraussichtlicheZeit + iZeitversatz));
}

const std::stringstream Scoutbuero::GebaudeAktivText() const
{
	 std::stringstream ssText;
	 ssText << "Die Mitarbeiter des\nScoutbueros suchen intensiv\nnach einem Geeignetem\nMitglied. Die Suche\ndauert voraussichtlich\nnoch " << getTimerstand();
	 return ssText;
}



void Scoutbuero::BeendenDerAusfuhrung()
{
	std::stringstream ssText;
	ssText << "Starke:Test\nAffinitaet: Test\nProzentualer Anteil: Test";
	cData->getKacheln(12).neueAnzeige(ssText.str(), 160, 99, 1, 1);
	cData->getKacheln(12).ButtonHinzufuegen(35, 400, 200, 30, 5, "Annehmen", *cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255,150,0), sf::Color::White, cData->getKacheln(12).getGroese().x, cData->getKacheln(12).getGroese().y);
	cData->getKacheln(12).ButtonHinzufuegen(35, 450, 200, 30, 6, "Ablehnen", *cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255,150,0), sf::Color::White, cData->getKacheln(12).getGroese().x, cData->getKacheln(12).getGroese().y);

	
	bProzessAktiv = false;	// Auf False setzen damit nicht der andere Text ausgegeben wird von aktAusbildung
	cData->getAnimationen().startBenarichtigung(true, "Suche erfolgreich Abgeschlossen");
}

void Scoutbuero::Annehmen()
{
	// EM dauerhaft in Data speichern
	cData->getKacheln(12).neueAnzeige("Error in Annehmen", 160, 99, 1, 1);
	aktualisierenInformationsText();
	cData->getKacheln(12).ButtonHinzufuegen(35, 450, 200, 30, 1, "Starten", *cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White, cData->getKacheln(12).getGroese().x, cData->getKacheln(12).getGroese().y);
	cData->getAnimationen().startBenarichtigung(true, "EM Angenomen");
}

void Scoutbuero::Ablehnen()
{
	//EM = nullptr
	cData->getKacheln(12).neueAnzeige("Error in Ablehnen", 160, 99, 1, 1);
	aktualisierenInformationsText();
	cData->getKacheln(12).ButtonHinzufuegen(35, 450, 200, 30, 1, "Starten", *cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White, cData->getKacheln(12).getGroese().x, cData->getKacheln(12).getGroese().y);
	cData->getAnimationen().startBenarichtigung(false, "EM Abgelehnt");
	bProzessAktiv = false;
}

inline void Scoutbuero::aktualisierenInformationsText()
{
	std::stringstream ssText;
	ssText << "Einselkaempfer Rekutieren\n(EM)\nEin EM bekommt\nein Teil der Finanzellen\nBehlohnung und hat\neine Affinitaet.\nDie Affinitaet erlaubt\ndie Ausstatung spezieller\nWaffen und bringt\nVorteile bei bestimmten\nAuftragen."; //\nSuchkosten: " << eRang * iKostenmitarbeiter * iVoraussichtlicheZeit << "\nVoraussichtliche dauer: " << iVoraussichtlicheZeit;
	
	cData->getKacheln(12).TextAendern(ssText.str(), 200);
}

void Scoutbuero::ErhohenDesMoeglichenRanges()
{
	if (cData->getiKontostand() > fUpgradeKosten[1] && iRangmin<6)								// �berpr�fen ob die Ausbildung bezahlt werden kann
	{
		iRangmin++;																							// Durchf�ren der Verbesserung 
		fUpgradeKosten[1] *= 1.6;								// Speichern der neuen Verbesserungskosten
		std::stringstream ss;
		ss << -fUpgradeKosten[1];
		eRang = static_cast<Rang>(rand() % 2 + iRangmin);
		iGebaeudeEinflussZeitFaktor = eRang;
		
		cData->setiKontostand(cData->getiKontostand() - fUpgradeKosten[1]);					// Abziehn der Verbesserungskosten
		cData->getAnimationen().startBenarichtigung(false, ss.str());
		//cData->getAnimationen().startUpgradeAnimation(3);

		
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
			aktualisierenInformationsText();
		}

		if (iRangmin == 6)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nwuerde erreicht.\nSie koennen diesen\nPrarameter nicht mehr\noprimieren";
			cData->getKacheln(14).neueAnzeige(ss.str(), 350, 1, 535, 95);
		}

		else
		{
			// Ausgabe des neuen Textes
			ss << "Das Scoutbuero\nfindet Einzelkampfer die\neinen hoeheren Rang\nund Potenzial habne\nKosten: " << fUpgradeKosten[1];
			cData->getKacheln(14).TextAendern(ss.str(), 320);
		}
	}	
}

