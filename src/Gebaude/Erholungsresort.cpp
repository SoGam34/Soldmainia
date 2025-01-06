#include "Erholungsresort.h"
#include <memory>

Erholungsresort::Erholungsresort(std::shared_ptr<Data>& data)
    : Gebaeude(data, 100, 1), Auswahl(data), EinheitsVPosition(0)
{
	UpgradeStats.GebaudeSpezielleFaktor = 1;
}

unsigned int Erholungsresort::getGebaeudeAusfuhrungskosten() const
{
	auto e = Daten->getMembers().at(EinheitsVPosition);
	return UpgradeStats.AusführungsReduzierungsKosten *
	       (VoraussichtlicheZeit + Zeitversatz) *
	       (e.first.has_value() ? e.first->getMemeberCount() : 1);
}

const std::stringstream Erholungsresort::getGebaudeAktivText() const
{
	// Der Text der warend des Trainings angezeigt wird
	auto e = Daten->getMembers()[EinheitsVPosition];
	std::stringstream ssText;
	ssText << "Die Einheit "
	       << (e.first.has_value() ? e.first->getName()
				       : e.second->getName())
	       << "\nwird gerade Versorgen\nDie Versorgen ist\nvorausicht "
		  "in "
	       << VoraussichtlicheZeit << "\nTagen abgeschlosen";
	return ssText;
}

void Erholungsresort::auswahlZuOrdnen(int Position)
{
	EinheitsVPosition = Position;
	leeren();
	beginneAufgabe();
}

void Erholungsresort::beendenDerAusfuhrung()
{
	// TODO(Einheit): Benarichtigung Erholt

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

void Erholungsresort::erhohenDerTraningsWirksamkeit()
{
	if (Daten->getKontostand() < UpgradeStats.GebaudeSpezielleKosten ||
	    UpgradeStats.GebaudeSpezielleUpgradeMaxLevel)
	{
		return;
	}

	Daten->abziehnVonKontostand(UpgradeStats.GebaudeSpezielleKosten);

	UpgradeStats.GebaudeSpezielleFaktor += 1;
	UpgradeStats.GebaudeSpezielleKosten *= 1.6;

	if (!ProgressStats.hasProgress)
	{
		berrechnungVoraussichtlicheZeit();
	}

	if (UpgradeStats.GebaudeSpezielleFaktor > 26)
	{
		UpgradeStats.GebaudeSpezielleUpgradeMaxLevel = true;
	}
}
