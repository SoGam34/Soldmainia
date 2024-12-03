#include "Gebaeude.h"

Gebaeude::Gebaeude(std::shared_ptr<Data> data, unsigned short int KostenFaktor,
		   unsigned short int ZeitFaktor)
    : Daten(data), ProzessAktiv(false), AufgabenDurchfuehrungZeitFaktor(1),
      AusfuhrungsKostenFaktor(KostenFaktor),
      GebaeudeEinflussZeitFaktor(ZeitFaktor)
{
	UpgradeStats = GebaeudeStats();

	Zeitversatz =
	    rand() % 5 + 3; // Festlegen des neuen Zeitversatzes mit dem

	berrechnungVoraussichtlicheZeit(); // hier gearbeitet wird
}

Gebaeude::~Gebaeude()
{
}

GebaeudeStats Gebaeude::getUpgradeStats()
{
	return UpgradeStats;
}

void Gebaeude::beginneAufgabe()
{
	if (Daten->getKontostand() >
	    getGebaeudeAusfuhrungskosten()) // �berpr�fen ob die Ausbildung
					    // bezahlt werden kann
	{
		std::stringstream ss;
		int temp = getGebaeudeAusfuhrungskosten();
		ss << -temp;
		// Daten->getAnimationen().startBenarichtigung(false, ss.str());
		// TODO UI Animation

		neuerTimer(VoraussichtlicheZeit);  // Start des Timers
		Daten->abziehnVonKontostand(temp));// Abziehn der gesamten Ausbildungskosten
		ProzessAktiv = true;		   // Auf true gesetzt damit der
				     // Ausbildungsvortschrit angezietgt wird
		Daten->getKacheln(ProzessHauptKachel)
		    .neueAnzeige(getGebaudeAktivText().str(), 200, 99, 1,
				 1); // neues Kachel Bild
	}
}

inline void Gebaeude::aktualisierenProzessZustand()
{
	Daten->getKacheln(ProzessHauptKachel)
	    .TextAendern(getGebaudeAktivText().str(), 200);
}

void Gebaeude::beschleunigungDerAufgabenDurchfuehrung()
{
	if (Daten->getKontostand() > UpgradeKosten[0] &&
	    AufgabenDurchfuehrungZeitFaktor >=
		0.1) // �berpr�fen ob die Ausbildung bezahlt werden kann
	{
		std::stringstream ss;
		ss << -UpgradeKosten[0];
		// Daten->getAnimationen().startBenarichtigung(false, ss.str());
		// TODO UI Animation
		// Daten->getAnimationen().startUpgradeAnimation(2,
		// Data->getBreite(), Data->getHohe());	TODO UI Animation

		Daten->abziehnVonKontostand(
		    UpgradeKosten[0]); // Abziehn der Verbesserungskosten

		UpgradeKosten[0] *=
		    1.2; // Speichern der neuen Verbesserungskosten
		AufgabenDurchfuehrungZeitFaktor -=
		    0.05; // Durchf�ren der Verbesserung

		ss.str("");
		if (!ProzessAktiv) // �berpr�ft ob ein Batillion ausgebildet
				   // wird, wenn ja wird die Anzeige und  Uhr
				   // nicht aktualiesiert da dies zu Anzeigebugs
				   // f�hrt
		{
			aktualisierenInformationsText();
			berrechnungVoraussichtlicheZeit();
		}

		if (AufgabenDurchfuehrungZeitFaktor < 0.10)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nwuerde erreicht.\nSie "
			      "koennen diesen\nPrarameter nicht "
			      "mehr\noprimieren";
			Daten->getKacheln(ProzessHauptKachel + 1)
			    .neueAnzeige(ss.str(), 350, 1, 285, 95);
		}

		else
		{
			// Ausgabe des neuen Textes
			ss << "Beschleunigt die\nAusbildungsdauer um "
			      "5%\nKosten:"
			   << UpgradeKosten[0];
			Daten->getKacheln(ProzessHauptKachel + 1)
			    .TextAendern(ss.str(), 350);
		}
	}
}

void Gebaeude::reduzierenDerAusfuhrungsKosten()
{
	if (Daten->getKontostand() > UpgradeKosten[2] &&
	    AusfuhrungsKostenFaktor >
		10) // �berpr�fen ob die Ausbildung bezahlt werden kann
	{
		std::stringstream ss;
		ss << -UpgradeKosten[2];
		// Daten->getAnimationen().startBenarichtigung(false, ss.str());
		// TODO UI Animation
		// Daten->getAnimationen().startUpgradeAnimation(4,
		// Data->getBreite(), Data->getHohe());	TODO UI Animation

		Daten->abziehnVonKontostand(
		    UpgradeKosten[2]); // Abziehn der Verbesserungskosten

		UpgradeKosten[2] *=
		    1.4; // Speichern der neuen Verbesserungskosten
		AusfuhrungsKostenFaktor -= 10;

		ss.str("");
		if (!ProzessAktiv) // �berpr�ft ob ein EM gesucht wird, wenn ja
				   // wird die Anzeige und  Uhr nicht
				   // aktualiesiert da dies zu Anzeigebugs f�hrt
		{
			berrechnungVoraussichtlicheZeit();
			aktualisierenInformationsText();
		}

		if (AusfuhrungsKostenFaktor == 10)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nwuerde erreicht.\nSie "
			      "koennen diesen\nPrarameter nicht "
			      "mehr\noprimieren";
			Daten->getKacheln(ProzessHauptKachel + 3)
			    .neueAnzeige(ss.str(), 350, 1, 785, 95);
		}

		else
		{
			ss << "Reduzierung der Kosten\nKosten: "
			   << UpgradeKosten[2];
			Daten->getKacheln(ProzessHauptKachel + 3)
			    .TextAendern(ss.str(), 350);
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
	     ((Daten->getBekanntheit() < 1000) ? 3
	      : (Daten->getBekanntheit() < 10000)
		  ? 2
		  : 1)); // Ermitteln der Bekanntheit und dem dadurch
			 // resultierendem Faktor

	neuerTimer(VoraussichtlicheZeit);
}

void Gebaeude::aktualisierenTimer()
{
	aktTimer(); // akktualiesieren der Uhr

	if (getTimerstand() + Zeitversatz == 0 &&
	    ProzessAktiv) // �berpr�fen ob die Zeit abgelaugen ist
		beendenDerAusfuhrung(); // Beenden der Ausbildung, da die
					// Ausbildung fertig ist

	else if (ProzessAktiv) // Aktualiesiern des Angezeigten Ausbildungs
			       // Fortschritts
		aktualisierenProzessZustand();
}
