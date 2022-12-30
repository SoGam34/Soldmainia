#include "Gebaeude.h"

Gebaeude::Gebaeude(short int iHauptKachel, short int UpgradeReihe)
{
	cData = nullptr;					// intiltilisieren mit nullptr zur prevention von Schaden die angerichtet werden könnten
	bProzessAktiv = false;				// Auf False setzen, da keine Aubildung statt findet

	iZeitversatz = rand() % 5 + 3;		// Festlegen des neuen Zeitversatzes mit dem 
	BerrechnungVoraussichtlicheZeit();	// hier gearbeitet wird 

	iProzessHauptKachel = iHauptKachel;
	iProzessUpgradeReihe = UpgradeReihe;
}

Gebaeude::Gebaeude(Data* data, short int iHauptKachel, short int UpgradeReihe)
{
	cData = data;						// intitlaiesieren von data 
	bProzessAktiv = false;				// Auf False setzen, da keine Aubildung statt findet

	iZeitversatz = rand() % 5 + 3;		// Festlegen des neuen Zeitversatzes mit dem 
	BerrechnungVoraussichtlicheZeit();	// hier gearbeitet wird 

	iProzessHauptKachel = iHauptKachel;
	iProzessUpgradeReihe = UpgradeReihe;
}

Gebaeude::~Gebaeude()
{
}

void Gebaeude::StartProzess()
{
	if (cData->getiKontostand() > ProzessKosten()) // überprüfen ob die Ausbildung bezahlt werden kann
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
	if (cData->getiKontostand() > cData->getfUpgradeKosten(iProzessUpgradeReihe, 0) && cData->getGeschwindikeitsfaktor(iProzessUpgradeReihe) >= 0.1)	// überprüfen ob die Ausbildung bezahlt werden kann
	{
		cData->setGeschwindikeitsFaktor(cData->getGeschwindikeitsfaktor(iProzessUpgradeReihe) - 0.05, iProzessUpgradeReihe);		// Durchfüren der Verbesserung 

		std::stringstream ss;
		ss << -(cData->getfUpgradeKosten(iProzessUpgradeReihe, 0));
		cData->getAnimationen().startBenarichtigung(false, ss.str());
		ss.clear();

		cData->setiKontostand(cData->getiKontostand() - cData->getfUpgradeKosten(iProzessUpgradeReihe, 0));					// Abziehn der Verbesserungskosten
		cData->setfUpgradeKosten(iProzessUpgradeReihe, 0, cData->getfUpgradeKosten(iProzessUpgradeReihe, 0) * 1.2);								// Speichern der neuen Verbesserungskosten

		cData->getAnimationen().startUpgradeAnimation(2);

		ss.str("");
		if (!bProzessAktiv)	// überprüft ob ein Batilion ausgebildet wird, wenn ja wird die Anzeige und  Uhr nicht aktualiesiert da dies zu Anzeigebugs führt
		{
			aktstd();
			BerrechnungVoraussichtlicheZeit();
		}

		if (cData->getGeschwindikeitsfaktor(iProzessUpgradeReihe) < 0.10)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nwürde erreicht.\nSie können diesen\nPrarameter nicht mehr\noprimieren";
			cData->getKacheln(iProzessHauptKachel+1).neuesBild(ss.str(), 350, 1, 285, 95);
		}

		else
		{
			// Ausgabe des neuen Textes
			ss << "Beschleunigt die\nAusbildungsdauer um 5%\nKosten:" << cData->getfUpgradeKosten(iProzessUpgradeReihe, 0);
			cData->getKacheln(iProzessHauptKachel+1).changeText(ss.str(), 350);
		}
	}
}

void Gebaeude::UpgradeKosten()
{
	if (cData->getiKontostand() > cData->getfUpgradeKosten(iProzessUpgradeReihe, 2) && cData->getProzessKostenFaktor(iProzessUpgradeReihe) > 10)	// überprüfen ob die Ausbildung bezahlt werden kann
	{
		cData->setProzessKostenFaktor( cData->getProzessKostenFaktor(iProzessUpgradeReihe) - 10, iProzessUpgradeReihe);																	// Durchfüren der Verbesserung 

		std::stringstream ss;
		ss << -(cData->getfUpgradeKosten(iProzessUpgradeReihe, 2));
		cData->getAnimationen().startBenarichtigung(false, ss.str());

		cData->setiKontostand(cData->getiKontostand() - cData->getfUpgradeKosten(iProzessUpgradeReihe, 2));			// Abziehn der Verbesserungskosten
		cData->setfUpgradeKosten(iProzessUpgradeReihe, 2, cData->getfUpgradeKosten(iProzessUpgradeReihe, 2) * 1.4);						// Speichern der neuen Verbesserungskosten	

		cData->getAnimationen().startUpgradeAnimation(4);

		ss.str("");
		if (!bProzessAktiv)	// überprüft ob ein EM gesucht wird, wenn ja wird die Anzeige und  Uhr nicht aktualiesiert da dies zu Anzeigebugs führt
		{
			BerrechnungVoraussichtlicheZeit();
			aktstd();
		}

		if (cData->getProzessKostenFaktor(iProzessUpgradeReihe) == 10)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nwürde erreicht.\nSie können diesen\nPrarameter nicht mehr\noprimieren";
			cData->getKacheln(iProzessHauptKachel+3).neuesBild(ss.str(), 350, 1, 785, 95);
		}

		else
		{
			ss << "Reduzierung der Kosten\nKosten: " << cData->getfUpgradeKosten(iProzessUpgradeReihe, 2);
			cData->getKacheln(iProzessHauptKachel+3).changeText(ss.str(), 350);
		}
	}
}

void Gebaeude::aktstd()
{
	std::stringstream ssText;
	ssText << "Einselkämpfer Rekutieren\n(EM)\nEin EM bekommt\nein Teil der Finanzellen\nBehlohnung und hat\neine Affinität.\nDie Affinität erlaubt\ndie Ausstatung spezieller\nWaffen und bringt\nVorteile bei bestimmten\nAuftragen."; //\nSuchkosten: " << eRang * iKostenmitarbeiter * iVoraussichtlicheZeit << "\nVoraussichtliche dauer: " << iVoraussichtlicheZeit;
	cData->getKacheln(12).changeText(ssText.str(), 200);
	ssText.clear();
}

void Gebaeude::BerrechnungVoraussichtlicheZeit()
{
	iVoraussichtlicheZeit = (iZeitversatz * cData->getiZeitFaktor(iProzessUpgradeReihe) * cData->getGeschwindikeitsfaktor(iProzessUpgradeReihe) * // Ermitteln der Zeit die Vorausichtlich für die Ausbildung gebraucht wird Unterberucksichtigung von der eines Faktors, der Größe, der Grundgeschwindikeit, der Bekanntheit
		((cData->getBekanntheit() < 1000) ? 3 : (cData->getBekanntheit() < 10000) ? 2 : 1));	 // Ermitteln der Bekanntheit und dem dadurch resultierendem Faktor

	neuerTimer(iVoraussichtlicheZeit);
}

void Gebaeude::updateTimer()
{
	aktTimer();									// akktualiesieren der Uhr

	if (getTimerstand() + iZeitversatz == 0 && bProzessAktiv)	// überprüfen ob die Zeit abgelaugen ist 
		EndeProzess();						// Beenden der Ausbildung, da die Ausbildung fertig ist 

	else if (bProzessAktiv)					// Aktualiesiern des Angezeigten Ausbildungs Fortschritts
		aktProzessZustand();
}
