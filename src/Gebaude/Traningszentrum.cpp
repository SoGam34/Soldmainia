#include "Traningszentrum.h"

Traningszentrum::Traningszentrum(std::shared_ptr<Data>& data)
    : Gebaeude(data, 100, 1), Auswahl(data), EinheitsVPosition(0),
      Wirksamkeitsgrad(1)
{
}

unsigned int Traningszentrum::getGebaeudeAusfuhrungskosten() const
{
	return AusfuhrungsKostenFaktor * (VoraussichtlicheZeit + Zeitversatz) *
	       Daten->getEinheiten()[EinheitsVPosition].getGrosse();
}

const std::stringstream Traningszentrum::getGebaudeAktivText() const
{
	// Der Text der warend des Trainings angezeigt wird
	std::stringstream ssText;
	ssText << "Die Einheit "
	       << Daten->getEinheiten()[EinheitsVPosition].getName()
	       << "\nwird gerade Trainiert\nDas Training ist\nvorausicht in "
	       << VoraussichtlicheZeit << "\nTagen abgeschlossen";
	return ssText;
}

void Traningszentrum::langeTrainingsDauer()
{
	GebaeudeEinflussZeitFaktor = 3;
	// sucheNachUnverletztenEinsetzbarenEinheiten();
}

void Traningszentrum::mittlereTrainingsDauer()
{
	GebaeudeEinflussZeitFaktor = 2;
	// sucheNachUnverletztenEinsetzbarenEinheiten();
}

void Traningszentrum::kurzeTraningsDauer()
{
	GebaeudeEinflussZeitFaktor = 1;
	// sucheNachUnverletztenEinsetzbarenEinheiten();
}

void Traningszentrum::auswahlZuOrdnen(int Position)
{
	EinheitsVPosition = Position;
	leeren();
	beginneAufgabe();
}

void Traningszentrum::beendenDerAusfuhrung()
{
	// TODO(Einheit): Benarichtigung Traningsende

	Zeitversatz = rand() % 5 + 3;
	berrechnungVoraussichtlicheZeit();

	ProzessAktiv = false;

	ProgressStats.hasProgress  = false;
	ProgressStats.ProgressText = "";

	Daten->getEinheiten()[EinheitsVPosition].xpHinzufugen(
	    Wirksamkeitsgrad * GebaeudeEinflussZeitFaktor);
}

void Traningszentrum::erhohenDerTraningsWirksamkeit()
{
	if (Daten->getKontostand() < UpgradeStats.GebaudeSpezielleKosten &&
	    UpgradeStats.GebaudeSpezielleUpgradeMaxLevel)
	{
		return;
	}

	Wirksamkeitsgrad += 1;
	UpgradeStats.GebaudeSpezielleKosten *= 1.6;

	Daten->abziehnVonKontostand(UpgradeStats.GebaudeSpezielleKosten);

	if (!ProzessAktiv)
	{
		berrechnungVoraussichtlicheZeit();
	}

	if (Wirksamkeitsgrad > 24)
	{
		UpgradeStats.GebaudeSpezielleUpgradeMaxLevel = true;
	}
}
