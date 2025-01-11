#include "Scoutbuero.h"
#include <cstdlib>
#include <iostream>

Scoutbuero::Scoutbuero(std::shared_ptr<Data>& data) : Gebaeude(data, 400, 1)
{
	UpgradeStats.GebaudeSpezielleFaktor = 1;
	Rang						= static_cast<Range>(					    // NOLINT
		 rand() % 2 + UpgradeStats.GebaudeSpezielleFaktor); // NOLINT
}

unsigned int Scoutbuero::getGebaeudeAusfuhrungskosten() const
{
	return (Rang * UpgradeStats.AusführungsReduzierungsKosten * (VoraussichtlicheZeit + Zeitversatz));
}

const std::stringstream Scoutbuero::getGebaudeAktivText() const
{
	std::stringstream ssText;
	ssText << "Die Mitarbeiter des\nScoutbueros suchen intensiv\nnach einem "
		    "geeignetem\nMitglied. Die Suche\ndauert voraussichtlich\nnoch "
		 << getTimerstand();
	return ssText;
}

void Scoutbuero::beendenDerAusfuhrung()
{
	// TODO(Einheit): Benarichtigung suche beendet

	ProgressStats.hasProgress  = false;
	ProgressStats.ProgressText = "";
}

void Scoutbuero::annehmenDerEinheit()
{
	// TODO(Einheit): Richtiges bennenungssystem
	std::string name;
	std::cout << "Die Ausbildung des Battilion ist beendet wie wollen sie das Battilion nennen? " << std::endl;
	std::cin >> name;

	int basis = Rangmin * 10;
	Daten->addEinzelkampfer(Einzelkampfer(static_cast<AbilityTyps>(rand() % 4), basis, basis, Rangmin * 15, name));

	ProgressStats.hasProgress  = false;
	ProgressStats.ProgressText = "";
}

void Scoutbuero::ablehnenDerEinheit()
{

	ProgressStats.hasProgress  = false;
	ProgressStats.ProgressText = "";
}

void Scoutbuero::erhohenDesMoeglichenRanges()
{
	if (Daten->getKontostand() < UpgradeStats.GebaudeSpezielleKosten || UpgradeStats.GebaudeSpezielleUpgradeMaxLevel)
	{
		UpgradeStats.GebaudeSpezielleFaktor++;
		UpgradeStats.GebaudeSpezielleKosten *= 1.6;

		Rang				   = static_cast<Range>(rand() % 2 + UpgradeStats.GebaudeSpezielleFaktor);
		GebaeudeEinflussZeitFaktor = Rang;

		Daten->abziehnVonKontostand(UpgradeStats.GebaudeSpezielleKosten);

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

		if (!ProgressStats.hasProgress)
		{
			berrechnungVoraussichtlicheZeit();
		}

		if (UpgradeStats.GebaudeSpezielleFaktor == 6)
		{
			UpgradeStats.GebaudeSpezielleUpgradeMaxLevel = true;
		}
	}
}
