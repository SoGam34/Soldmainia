#include "Traningszentrum.h"

Traningszentrum::Traningszentrum(std::shared_ptr<Data>& data)
    : Gebaeude(data, 100, 1), Auswahl(data), EinheitsVPosition(0)
{
	UpgradeStats.GebaudeSpezielleFaktor = 1;
}

unsigned int Traningszentrum::getGebaeudeAusfuhrungskosten() const
{
	auto e = Daten->getMembers().at(EinheitsVPosition);
	return UpgradeStats.AusführungsReduzierungsKosten *
	       (VoraussichtlicheZeit + Zeitversatz) *
	       (e.first.has_value() ? e.first->getMemeberCount() : 1);
}

const std::stringstream Traningszentrum::getGebaudeAktivText() const
{
	// Der Text der warend des Trainings angezeigt wird
	auto e = Daten->getMembers()[EinheitsVPosition];
	std::stringstream ssText;
	ssText << "Die Einheit "
	       << (e.first.has_value() ? e.first->getName()
				       : e.second->getName())
	       << "\nwird gerade Trainiert\nDas Training ist\nvorausicht in "
	       << VoraussichtlicheZeit << "\nTagen abgeschlossen";
	return ssText;
}

void Traningszentrum::langeTrainingsDauer()
{
	GebaeudeEinflussZeitFaktor = 3;
}

void Traningszentrum::mittlereTrainingsDauer()
{
	GebaeudeEinflussZeitFaktor = 2;
}

void Traningszentrum::kurzeTraningsDauer()
{
	GebaeudeEinflussZeitFaktor = 1;
}

void Traningszentrum::auswahlZuOrdnen(int Position)
{
	EinheitsVPosition = Position;
	beginneAufgabe();
}

void Traningszentrum::beendenDerAusfuhrung()
{
	// TODO(Einheit): Benarichtigung Traningsende

	Zeitversatz = rand() % 5 + 3;
	berrechnungVoraussichtlicheZeit();

	ProgressStats.hasProgress  = false;
	ProgressStats.ProgressText = "";

	auto e = Daten->getMembers().at(EinheitsVPosition);

	int xp =
	    UpgradeStats.GebaudeSpezielleFaktor * GebaeudeEinflussZeitFaktor;

	if (e.first.has_value())
	{
		e.first->addExpierience(xp);
		return;
	}

	e.second->addExpierience(xp);
}

void Traningszentrum::erhohenDerTraningsWirksamkeit()
{
	if (Daten->getKontostand() < UpgradeStats.GebaudeSpezielleKosten ||
	    UpgradeStats.GebaudeSpezielleUpgradeMaxLevel)
	{
		return;
	}

	UpgradeStats.GebaudeSpezielleFaktor += 1;
	UpgradeStats.GebaudeSpezielleKosten *= 1.6;

	Daten->abziehnVonKontostand(UpgradeStats.GebaudeSpezielleKosten);

	if (!ProgressStats.hasProgress)
	{
		berrechnungVoraussichtlicheZeit();
	}

	if (UpgradeStats.GebaudeSpezielleFaktor > 24)
	{
		UpgradeStats.GebaudeSpezielleUpgradeMaxLevel = true;
	}
}
