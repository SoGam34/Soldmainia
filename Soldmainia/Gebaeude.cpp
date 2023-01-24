#include "Gebaeude.h"

Gebaeude::Gebaeude(Data* data, unsigned short int iHauptKachel, unsigned short int KostenFaktor, unsigned short int ZeitFaktor)
{
	cData = data;						// intitlaiesieren von data 
	bProzessAktiv = false;				// Auf False setzen, da keine Aubildung statt findet

	iProzessHauptKachel = iHauptKachel;

	iGeschwindikeitsFaktor = 1;

	iKostenFaktor = KostenFaktor;

	iZeitFaktor = ZeitFaktor;

	fUpgradeKosten[0] = 100;
	fUpgradeKosten[1] = 100;
	fUpgradeKosten[2] = 100;
	
	iZeitversatz = rand() % 5 + 3;		// Festlegen des neuen Zeitversatzes mit dem 
	BerrechnungVoraussichtlicheZeit();	// hier gearbeitet wird 
}

Gebaeude::~Gebaeude()
{
}

void Gebaeude::StartProzess()
{
	if (cData->getiKontostand() > ProzessKosten()) // �berpr�fen ob die Ausbildung bezahlt werden kann
	{
		std::stringstream ss;
		ss << -ProzessKosten();
		cData->getAnimationen().startBenarichtigung(false, ss.str());

		neuerTimer(iVoraussichtlicheZeit);																	// Start des Timers	
		cData->setiKontostand(cData->getiKontostand() - ProzessKosten());	// Abziehn der gesamten Ausbildungskosten
		bProzessAktiv = true;																			// Auf true gesetzt damit der Ausbildungsvortschrit angezietgt wird 
		cData->getKacheln(iProzessHauptKachel).neuesBild(ProzessText().str(), 300, 99, 1, 1);	//neues Kachel Bild	
	}
}

void Gebaeude::aktProzessZustand()
{
	cData->getKacheln(iProzessHauptKachel).changeText(ProzessText().str(), 300);
}

void Gebaeude::UpgradeGeschwindikeit()
{
	if (cData->getiKontostand() > fUpgradeKosten[0] && iGeschwindikeitsFaktor >= 0.1)	// �berpr�fen ob die Ausbildung bezahlt werden kann
	{
		std::stringstream ss;
		ss << -fUpgradeKosten[0];
		cData->getAnimationen().startBenarichtigung(false, ss.str());
		cData->getAnimationen().startUpgradeAnimation(2);

		cData->setiKontostand(cData->getiKontostand() - fUpgradeKosten[0]);					// Abziehn der Verbesserungskosten
		
		fUpgradeKosten[0] *= 1.2;								// Speichern der neuen Verbesserungskosten
		iGeschwindikeitsFaktor -= 0.05;		// Durchf�ren der Verbesserung 

		ss.str("");
		if (!bProzessAktiv)	// �berpr�ft ob ein Batilion ausgebildet wird, wenn ja wird die Anzeige und  Uhr nicht aktualiesiert da dies zu Anzeigebugs f�hrt
		{
			aktstd();
			BerrechnungVoraussichtlicheZeit();
		}

		if (iGeschwindikeitsFaktor < 0.10)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nw�rde erreicht.\nSie k�nnen diesen\nPrarameter nicht mehr\noprimieren";
			cData->getKacheln(iProzessHauptKachel+1).neuesBild(ss.str(), 350, 1, 285, 95);
		}

		else
		{
			// Ausgabe des neuen Textes
			ss << "Beschleunigt die\nAusbildungsdauer um 5%\nKosten:" << fUpgradeKosten[0];
			cData->getKacheln(iProzessHauptKachel+1).changeText(ss.str(), 350);
		}
	}
}

void Gebaeude::UpgradeKosten()
{
	if (cData->getiKontostand() > fUpgradeKosten[2] && iKostenFaktor > 10)	// �berpr�fen ob die Ausbildung bezahlt werden kann
	{
		std::stringstream ss;
		ss << -fUpgradeKosten[2];
		cData->getAnimationen().startBenarichtigung(false, ss.str());
		cData->getAnimationen().startUpgradeAnimation(4);
		
		cData->setiKontostand(cData->getiKontostand() - fUpgradeKosten[2]);			// Abziehn der Verbesserungskosten
		
		fUpgradeKosten[2] *= 1.4;						// Speichern der neuen Verbesserungskosten	
		iKostenFaktor -= 10;

		ss.str("");
		if (!bProzessAktiv)	// �berpr�ft ob ein EM gesucht wird, wenn ja wird die Anzeige und  Uhr nicht aktualiesiert da dies zu Anzeigebugs f�hrt
		{
			BerrechnungVoraussichtlicheZeit();
			aktstd();
		}

		if (iKostenFaktor == 10)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nw�rde erreicht.\nSie k�nnen diesen\nPrarameter nicht mehr\noprimieren";
			cData->getKacheln(iProzessHauptKachel+3).neuesBild(ss.str(), 350, 1, 785, 95);
		}

		else
		{
			ss << "Reduzierung der Kosten\nKosten: " << fUpgradeKosten[2];
			cData->getKacheln(iProzessHauptKachel+3).changeText(ss.str(), 350);
		}
	}
}

void Gebaeude::BerrechnungVoraussichtlicheZeit()
{
	iVoraussichtlicheZeit = (iZeitversatz * iZeitFaktor * iGeschwindikeitsFaktor * // Ermitteln der Zeit die Vorausichtlich f�r die Ausbildung gebraucht wird Unterberucksichtigung von der eines Faktors, der Gr��e, der Grundgeschwindikeit, der Bekanntheit
		((cData->getBekanntheit() < 1000) ? 3 : (cData->getBekanntheit() < 10000) ? 2 : 1));	 // Ermitteln der Bekanntheit und dem dadurch resultierendem Faktor

	neuerTimer(iVoraussichtlicheZeit);
}

void Gebaeude::updateTimer()
{
	aktTimer();									// akktualiesieren der Uhr

	if (getTimerstand() + iZeitversatz == 0 && bProzessAktiv)	// �berpr�fen ob die Zeit abgelaugen ist 
		EndeProzess();						// Beenden der Ausbildung, da die Ausbildung fertig ist 

	else if (bProzessAktiv)					// Aktualiesiern des Angezeigten Ausbildungs Fortschritts
		aktProzessZustand();
}