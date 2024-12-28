#include "Erholungsresort.h"

Erholungsresort::Erholungsresort(std::shared_ptr<Data>& data)
    : Gebaeude(data, 100, 1), Auswahl(data), EinheitsVPosition(0),
      Wirksamkeitsgrad(1)
{
}

unsigned int Erholungsresort::getGebaeudeAusfuhrungskosten() const
{
	return AusfuhrungsKostenFaktor * (VoraussichtlicheZeit + Zeitversatz) *
	       Daten->getEinheiten()[EinheitsVPosition].getGrosse();
}

const std::stringstream Erholungsresort::getGebaudeAktivText() const
{
	// Der Text der warend des Trainings angezeigt wird
	std::stringstream ssText;
	ssText << "Die Einheit "
	       << Daten->getEinheiten()[EinheitsVPosition].getName()
	       << "\nwird gerade Versorgen\nDie Versorgen ist\nvorausicht in "
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

	ProzessAktiv = false;

	ProgressStats.hasProgress  = false;
	ProgressStats.ProgressText = "";

	Daten->getEinheiten()[EinheitsVPosition].xpHinzufugen(
	    Wirksamkeitsgrad * GebaeudeEinflussZeitFaktor);
}

void Erholungsresort::erhohenDerTraningsWirksamkeit()
{
	if (Daten->getKontostand() < UpgradeStats.GebaudeSpezielleKosten &&
	    UpgradeStats.GebaudeSpezielleUpgradeMaxLevel)
	{
		return;
	}

	Daten->abziehnVonKontostand(UpgradeStats.GebaudeSpezielleKosten);

	Wirksamkeitsgrad += 1;
	UpgradeStats.GebaudeSpezielleKosten *= 1.6;

	if (!ProzessAktiv)
	{
		berrechnungVoraussichtlicheZeit();
	}

	if (Wirksamkeitsgrad > 26)
	{
		UpgradeStats.GebaudeSpezielleUpgradeMaxLevel = true;
	}
}
