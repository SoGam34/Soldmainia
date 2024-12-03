#include "Scoutbuero.h"

Scoutbuero::Scoutbuero(std::shared_ptr<Data> data)
    : Gebaeude(data, 400, 1), Rangmin(1)
{
	Rang = static_cast<Range>(rand() % 2 + Rangmin);
	// iLevel[0] = iLevel[1] = iLevel[2] = 0;
}

Scoutbuero::~Scoutbuero()
{
}

unsigned const int Scoutbuero::getGebaeudeAusfuhrungskosten() const
{
	return (Rang * AusfuhrungsKostenFaktor *
		(VoraussichtlicheZeit + Zeitversatz));
}

const std::stringstream Scoutbuero::getGebaudeAktivText() const
{
	std::stringstream ssText;
	ssText
	    << "Die Mitarbeiter des\nScoutbueros suchen intensiv\nnach einem "
	       "geeignetem\nMitglied. Die Suche\ndauert voraussichtlich\nnoch "
	    << getTimerstand();
	return ssText;
}

void Scoutbuero::beendenDerAusfuhrung()
{
	std::stringstream ssText;
	ssText << "Staerke:Test\nAffinitaet: Test\nProzentualer Anteil: Test";
	Daten->getKacheln(12).neueAnzeige(ssText.str(), 160, 99, 1, 1);
	Daten->getKacheln(12).ButtonHinzufuegen(
	    35, 400, 200, 30, 5, "Annehmen", *Daten->getFont(),
	    sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0),
	    sf::Color::White, Data->getKacheln(12).getGroese().x,
	    Data->getKacheln(12).getGroese().y);
	Daten->getKacheln(12).ButtonHinzufuegen(
	    35, 450, 200, 30, 6, "Ablehnen", *Daten->getFont(),
	    sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0),
	    sf::Color::White, Data->getKacheln(12).getGroese().x,
	    Data->getKacheln(12).getGroese().y);

	ProzessAktiv = false; // Auf False setzen damit nicht der andere Text
			      // ausgegeben wird von aktAusbildung
	// Daten->getAnimationen().startBenarichtigung(true, "Suche erfolgreich
	// abgeschlossen");	TODO UI Animation
}

void Scoutbuero::annehmenDerEinheit()
{
	// EM dauerhaft in Data speichern
	Daten->getKacheln(12).neueAnzeige("Error in Annehmen", 160, 99, 1, 1);
	aktualisierenInformationsText();
	Daten->getKacheln(12).ButtonHinzufuegen(
	    35, 450, 200, 30, 1, "Starten", *Daten->getFont(), sf::Color::Black,
	    sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White,
	    Data->getKacheln(12).getGroese().x,
	    Data->getKacheln(12).getGroese().y);
	// Daten->getAnimationen().startBenarichtigung(true, "EM Angenomen");
	// TODO UI Animation
}

void Scoutbuero::ablehnenDerEinheit()
{
	// EM = nullptr
	Daten->getKacheln(12).neueAnzeige("Error in Ablehnen", 160, 99, 1, 1);
	aktualisierenInformationsText();
	Daten->getKacheln(12).ButtonHinzufuegen(
	    35, 450, 200, 30, 1, "Starten", *Daten->getFont(), sf::Color::Black,
	    sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White,
	    Data->getKacheln(12).getGroese().x,
	    Data->getKacheln(12).getGroese().y);
	// Daten->getAnimationen().startBenarichtigung(false, "EM Abgelehnt");
	// TODO UI Animation
	ProzessAktiv = false;
}

inline void Scoutbuero::aktualisierenInformationsText()
{
	std::stringstream ssText;
	ssText
	    << "Einselkaempfer rekutieren\n(EM)\nEin EM bekommt\nein Teil der "
	       "finanzellen\nBelohnung und hat\neine Affinitaet.\nDie "
	       "Affinitaet erlaubt\ndie Ausstatung spezieller\nWaffen und "
	       "bringt\nVorteile bei bestimmten\nAuftraegen."; //\nSuchkosten: "
							       //<< eRang *
							       // iKostenmitarbeiter
							       //* iVoraussichtlicheZeit << "\nVoraussichtliche dauer: " << iVoraussichtlicheZeit;

	Daten->getKacheln(12).TextAendern(ssText.str(), 200);
}

void Scoutbuero::erhohenDesMoeglichenRanges()
{
	if (Daten->getKontostand() > UpgradeKosten[1] &&
	    Rangmin < 6) // �berpr�fen ob die Ausbildung bezahlt werden kann
	{
		Rangmin++; // Durchf�ren der Verbesserung
		UpgradeKosten[1] *=
		    1.6; // Speichern der neuen Verbesserungskosten
		std::stringstream ss;
		ss << -UpgradeKosten[1];
		Rang = static_cast<Range>(rand() % 2 + Rangmin);
		GebaeudeEinflussZeitFaktor = Rang;

		Daten->abziehnVonKontostand(
		    UpgradeKosten[1]); // Abziehn der Verbesserungskosten
		// Daten->getAnimationen().startBenarichtigung(false, ss.str());
		// TODO UI Animation
		// cData->getAnimationen().startUpgradeAnimation(3);

		// Erzeugen eines EM Objektes
		switch (Rang)
		{
		case S:
		{
			Zeitversatz = rand() % 20 + 7;
			berrechnungVoraussichtlicheZeit();
		}
		break;
		case A:
		{
			Zeitversatz = rand() % 20 + 9;
			berrechnungVoraussichtlicheZeit();
		}
		break;
		case B:
		{
			Zeitversatz = rand() % 20 + 11;
			berrechnungVoraussichtlicheZeit();
		}
		break;
		case C:
		{
			Zeitversatz = rand() % 20 + 13;
			berrechnungVoraussichtlicheZeit();
		}
		break;
		case D:
		{
			Zeitversatz = rand() % 20 + 15;
			berrechnungVoraussichtlicheZeit();
		}
		break;
		case E:
		{
			Zeitversatz = rand() % 20 + 17;
			berrechnungVoraussichtlicheZeit();
		}
		break;
		case F:
		{
			Zeitversatz = rand() % 20 + 19;
			berrechnungVoraussichtlicheZeit();
		}
		break;
		}

		ss.str("");
		if (!ProzessAktiv) // �berpr�ft ob ein Batillion ausgebildet
				   // wird, wenn ja wird die Anzeige und  Uhr
				   // nicht aktualiesiert da dies zu Anzeigebugs
				   // f�hrt
		{
			berrechnungVoraussichtlicheZeit();
			aktualisierenInformationsText();
		}

		if (Rangmin == 6)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nwuerde erreicht.\nSie "
			      "koennen diesen\nPrarameter nicht "
			      "mehr\noprimieren";
			Daten->getKacheln(14).neueAnzeige(ss.str(), 350, 1, 535,
							  95);
		}

		else
		{
			// Ausgabe des neuen Textes
			ss << "Das Scoutbuero\nfindet Einzelkaempfer "
			      "die\neinen hoeheren Rang\nund Potenzial "
			      "haben\nKosten: "
			   << UpgradeKosten[1];
			Daten->getKacheln(14).TextAendern(ss.str(), 320);
		}
	}
}
