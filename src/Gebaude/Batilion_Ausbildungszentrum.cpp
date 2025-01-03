#include "Batilion_Ausbildungszentrum.h"

Batillion_Ausbildungszentrum::Batillion_Ausbildungszentrum(
    std::shared_ptr<Data>& data)
    : Gebaeude(data, 70, 10)
{
	UpgradeStats.GebaudeSpezielleFaktor=1;
}

unsigned int Batillion_Ausbildungszentrum::getGebaeudeAusfuhrungskosten() const
{
	return UpgradeStats.AusführungsReduzierungsKosten * (VoraussichtlicheZeit + Zeitversatz);
}

const std::stringstream
Batillion_Ausbildungszentrum::getGebaudeAktivText() const
{
	// Der Text der warend der Ausbildung angezeigt wird
	std::stringstream ssText;
	ssText << "Ausbildung eines neuen \nBatillions ist im Gang.\n"
	       << "Das Batillion wird aus\n"
	       << Batillionsgroesse << " Mitgliedern bestehen.\n"
	       << "Die Ausbildung wird in\n"
	       << getTimerstand() << " Tagen vorausichtlich\nfertig sein.";
	return ssText;
}

void Batillion_Ausbildungszentrum::erhoheEinheitsGrosse()
{
	// Erhoht die Gesamtanzahl der Soldaten in dem Batillion und
	// aktualiesiert die Ausgabe
	Batillionsgroesse += 1;
	GebaeudeEinflussZeitFaktor = Batillionsgroesse;
	berrechnungVoraussichtlicheZeit();
}

void Batillion_Ausbildungszentrum::reduziereEinheitsGrosse()
{
	// Reduziert die Gesamtanzahl der Soldaten in dem Batillion und
	// aktualiesiert die Ausgabe
	Batillionsgroesse -= 1;
	GebaeudeEinflussZeitFaktor = Batillionsgroesse;
	berrechnungVoraussichtlicheZeit();
}

void Batillion_Ausbildungszentrum::beendenDerAusfuhrung()
{
	// TODO(): Generierung eines Batillions

	ProgressStats.hasProgress  = false;
	ProgressStats.ProgressText = "";
}

void Batillion_Ausbildungszentrum::vorbereiten_neueAusbildung()
{
	// neues Kachel Bild
	Zeitversatz = rand() % 5 + 3;
	berrechnungVoraussichtlicheZeit();

	std::stringstream ssText; // Der Text der Angezeigt werden soll
	ssText << "Neues Batillion ausbilden\nGroesse: " << Batillionsgroesse
	       << "\nKampfkraft: " << Batillionsgroesse * 10 * UpgradeStats.GebaudeSpezielleFaktor
	       << "\nKosten: "
	       << UpgradeStats.AusführungsReduzierungsKosten *
		      VoraussichtlicheZeit
	       << "\nVoraussichtlich fertig in: " << VoraussichtlicheZeit;
}

void Batillion_Ausbildungszentrum::erhohenDerGrundstarke()
{
	if (Daten->getKontostand() < UpgradeStats.GebaudeSpezielleKosten ||
	    UpgradeStats.GebaudeSpezielleUpgradeMaxLevel)
	{
		return;
	}

	Daten->abziehnVonKontostand(UpgradeStats.GebaudeSpezielleKosten);

	UpgradeStats.GebaudeSpezielleKosten *= 1.6;
	UpgradeStats.GebaudeSpezielleFaktor += 1;

	if (!ProgressStats.hasProgress)
	{
		berrechnungVoraussichtlicheZeit();
	}

	if (UpgradeStats.GebaudeSpezielleFaktor > 24)
	{
		UpgradeStats.GebaudeSpezielleUpgradeMaxLevel = true;
	}
}
