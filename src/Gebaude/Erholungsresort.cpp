#include "Erholungsresort.h"
#include "Gebaeude.h"

Erholungsresort::Erholungsresort(std::shared_ptr<Data>& data)
	: Gebaeude(data, 100, 1), EinheitsVPosition(0), Wirksamkeitsgrad(1)
{
	UpgradeStats.GebaudeSpezielleFaktor = 1;
}

unsigned int Erholungsresort::getGebaeudeAusfuhrungskosten() const
{
	int soldierCount = 1;
	if (auto e = std::get_if<Battilion>(&Daten->getMembers().at(EinheitsVPosition)))
	{
		soldierCount = e->getMemeberCount();
	}
	return UpgradeStats.AusführungsReduzierungsKosten * (VoraussichtlicheZeit + Zeitversatz) * soldierCount;
}

const std::stringstream Erholungsresort::getGebaudeAktivText() const
{
	// Der Text der warend des Trainings angezeigt wird
	auto e = getAsEinheit(Daten->getMembers().at(EinheitsVPosition));
	std::stringstream ssText;
	ssText << "Die Einheit " << e->getName()
		 << "\nwird gerade Versorgen\nDie Versorgen ist\nvorausicht "
		    "in "
		 << VoraussichtlicheZeit << "\nTagen abgeschlosen";
	return ssText;
}

void Erholungsresort::auswahlZuOrdnen(int Position)
{
	EinheitsVPosition = Position;
	beginneAufgabe();
}

void Erholungsresort::beendenDerAusfuhrung()
{
	// TODO(Einheit): Benarichtigung Erholt

	Zeitversatz = rand() % 5 + 3;
	berrechnungVoraussichtlicheZeit();

	ProgressStats.hasProgress  = false;
	ProgressStats.ProgressText = "";

	auto e = getAsEinheit(Daten->getMembers().at(EinheitsVPosition));

	e->recoverHealth(UpgradeStats.GebaudeSpezielleFaktor);
	e->recoverMental(UpgradeStats.GebaudeSpezielleFaktor);
}

void Erholungsresort::erhohenDerTraningsWirksamkeit()
{
	if (Daten->getKontostand() < UpgradeStats.GebaudeSpezielleKosten || UpgradeStats.GebaudeSpezielleUpgradeMaxLevel)
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
