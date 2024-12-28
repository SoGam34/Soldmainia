#include "Gebaeude.h"
#include <sstream>

Gebaeude::Gebaeude(std::shared_ptr<Data> data, unsigned short int KostenFaktor,
		   unsigned short int ZeitFaktor)
    : Daten(data), ProzessAktiv(false), AufgabenDurchfuehrungZeitFaktor(1),
      AusfuhrungsKostenFaktor(KostenFaktor),
      GebaeudeEinflussZeitFaktor(ZeitFaktor)
{
	UpgradeStats  = GebaeudeUpgradeStats();
	ProgressStats = InProgressStats();

	Zeitversatz =
	    rand() % 5 + 3; // Festlegen des neuen Zeitversatzes mit dem

	berrechnungVoraussichtlicheZeit(); // hier gearbeitet wird
}

GebaeudeUpgradeStats Gebaeude::getUpgradeStats()
{
	return UpgradeStats;
}
InProgressStats Gebaeude::getProgressStats()
{
	return ProgressStats;
}

void Gebaeude::beginneAufgabe()
{
	if (Daten->getKontostand() > getGebaeudeAusfuhrungskosten())
	{
		neuerTimer(VoraussichtlicheZeit);
		Daten->abziehnVonKontostand(getGebaeudeAusfuhrungskosten());
		ProzessAktiv		   = true;
		std::stringstream temp	   = getGebaudeAktivText();
		ProgressStats.ProgressText = temp.str();
		ProgressStats.hasProgress  = true;
	}
}

inline void Gebaeude::aktualisierenProzessZustand()
{
	std::stringstream temp	   = getGebaudeAktivText();
	ProgressStats.ProgressText = temp.str();
}

void Gebaeude::beschleunigungDerAufgabenDurchfuehrung()
{
	if (Daten->getKontostand() > UpgradeStats.BeschlaunigunsKosten &&
	    AufgabenDurchfuehrungZeitFaktor >= 0.1)
	{
		Daten->abziehnVonKontostand(UpgradeStats.BeschlaunigunsKosten);

		UpgradeStats.BeschlaunigunsKosten *= 1.2;
		AufgabenDurchfuehrungZeitFaktor -= 0.05;

		if (!ProzessAktiv)
		{
			berrechnungVoraussichtlicheZeit();
		}

		if (AufgabenDurchfuehrungZeitFaktor < 0.10)
		{
			UpgradeStats.BeschlaunigungsUpgradeMaxLevel = true;
		}
	}
}

void Gebaeude::reduzierenDerAusfuhrungsKosten()
{
	if (Daten->getKontostand() >
		UpgradeStats.AusführungsReduzierungsKosten &&
	    AusfuhrungsKostenFaktor > 10)
	{
		Daten->abziehnVonKontostand(
		    UpgradeStats.AusführungsReduzierungsKosten);

		UpgradeStats.AusführungsReduzierungsKosten *= 1.4;
		AusfuhrungsKostenFaktor -= 10;

		if (!ProzessAktiv)
		{
			berrechnungVoraussichtlicheZeit();
		}

		if (AusfuhrungsKostenFaktor == 10)
		{
			UpgradeStats.AusführungsReduzierungsUpgradeMaxLevel =
			    false;
		}
	}
}

void Gebaeude::berrechnungVoraussichtlicheZeit()
{
	VoraussichtlicheZeit =
	    (Zeitversatz * AufgabenDurchfuehrungZeitFaktor *
	     GebaeudeEinflussZeitFaktor * // Ermitteln der Zeit die
					  // Vorausichtlich f�r die Ausbildung
					  // gebraucht wird
					  // Unterberucksichtigung von der eines
					  // Faktors, der Gr��e, der
					  // Grundgeschwindikeit, der
					  // Bekanntheit
	     ((Daten->getBekanntheit() < 1000)	  ? 3
	      : (Daten->getBekanntheit() < 10000) ? 2
						  : 1));

	neuerTimer(VoraussichtlicheZeit);
}

void Gebaeude::aktualisierenTimer()
{
	aktTimer(); // akktualiesieren der Uhr

	if (getTimerstand() + Zeitversatz == 0 && ProzessAktiv)
	{
		beendenDerAusfuhrung();
	}

	else if (ProzessAktiv)
	{
		aktualisierenProzessZustand();
	}
}
