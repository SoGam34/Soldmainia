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

unsigned int Scoutbuero::getGebaeudeAusfuhrungskosten() const
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
	/*Daten->getKacheln(12).neueAnzeige(ssText.str(), 160, 99, 1, 1);
	Daten->getKacheln(12).ButtonHinzufuegen(
	    35, 400, 200, 30, 5, "Annehmen", *Daten->getFont(),
	sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0),
	sf::Color::White, Data->getKacheln(12).getGroese().x,
	Data->getKacheln(12).getGroese().y);
	Daten->getKacheln(12).ButtonHinzufuegen(
	    35, 450, 200, 30, 6, "Ablehnen", *Daten->getFont(),
	sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0),
	sf::Color::White, Data->getKacheln(12).getGroese().x,
	Data->getKacheln(12).getGroese().y);*/

	ProzessAktiv =
	    false; // Auf False setzen damit nicht der andere Text
		   // ausgegeben wird von aktAusbildung
		   // Daten->getAnimationen().startBenarichtigung(true, "Suche
		   // erfolgreich abgeschlossen");	TODO UI Animation
}

void Scoutbuero::annehmenDerEinheit()
{
	// TODO(Einheit): Eine neue Einheit hinzufügen

	ProgressStats.hasProgress  = false;
	ProgressStats.ProgressText = "";

	ProzessAktiv = false;
}

void Scoutbuero::ablehnenDerEinheit()
{
	// TODO(Einheit): Löschen

	ProgressStats.hasProgress  = false;
	ProgressStats.ProgressText = "";

	ProzessAktiv = false;
}

void Scoutbuero::erhohenDesMoeglichenRanges()
{
	if (Daten->getKontostand() > UpgradeStats.GebaudeSpezielleKosten &&
	    Rangmin < 6)
	{
		Rangmin++;
		UpgradeStats.GebaudeSpezielleKosten *= 1.6;

		Rang = static_cast<Range>(rand() % 2 + Rangmin);
		GebaeudeEinflussZeitFaktor = Rang;

		Daten->abziehnVonKontostand(
		    UpgradeStats.GebaudeSpezielleKosten);

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

		if (!ProzessAktiv)
		{
			berrechnungVoraussichtlicheZeit();
		}

		if (Rangmin == 6)
		{
			UpgradeStats.GebaudeSpezielleUpgradeMaxLevel = true;
		}
	}
}
