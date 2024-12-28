#include "Batilion_Ausbildungszentrum.h"

Batillion_Ausbildungszentrum::Batillion_Ausbildungszentrum(
    std::shared_ptr<Data> data)
    : Gebaeude(data, 70, 10)
{
}

unsigned int Batillion_Ausbildungszentrum::getGebaeudeAusfuhrungskosten() const
{
	return AusfuhrungsKostenFaktor * (VoraussichtlicheZeit + Zeitversatz);
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
	ProzessAktiv = false;
	// TODO(): Generierung eines Batillions
}

void Batillion_Ausbildungszentrum::vorbereiten_neueAusbildung()
{
	// neues Kachel Bild
	Zeitversatz =
	    rand() % 5 +
	    3; // Berechnung der Ausbildungsdauer des n�chsten Batillions
	berrechnungVoraussichtlicheZeit();

	std::stringstream ssText; // Der Text der Angezeigt werden soll
	ssText << "Neues Batillion ausbilden\nGroesse: " << Batillionsgroesse
	       << "\nKampfkraft: " << Batillionsgroesse * 10 * Grundstaerke
	       << "\nKosten: " << AusfuhrungsKostenFaktor * VoraussichtlicheZeit
	       << "\nVoraussichtlich fertig in: " << VoraussichtlicheZeit;
}

void Batillion_Ausbildungszentrum::erhohenDerGrundstarke()
{
	if (Daten->getKontostand() > UpgradeStats.GebaudeSpezielleKosten &&
	    Grundstaerke < 25)
	{
		Grundstaerke += 1;

		Daten->abziehnVonKontostand(
		    UpgradeStats.GebaudeSpezielleKosten); 
		UpgradeStats.GebaudeSpezielleKosten *=
		    1.6; 
		    
		if (!ProzessAktiv)
		{
			berrechnungVoraussichtlicheZeit();
		}

		if (Grundstaerke > 24)
		{
			UpgradeStats.GebaudeSpezielleUpgradeMaxLevel=true;
		}
	}
}
