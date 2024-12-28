#include "Scoutbuero.h"

Scoutbuero::Scoutbuero(std::shared_ptr<Data>& data)
    : Gebaeude(data, 400, 1), Rangmin(1)
{
	Rang = static_cast<Range>(rand() % 2 + Rangmin); // NOLINT
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
	//TODO(Einheit): Benarichtigung suche beendet

	ProzessAktiv		   = false;

	ProgressStats.hasProgress  = false;
	ProgressStats.ProgressText = "";
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
	if (Daten->getKontostand() < UpgradeStats.GebaudeSpezielleKosten &&
	    UpgradeStats.GebaudeSpezielleUpgradeMaxLevel)
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
