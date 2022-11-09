#include "Scoutb�ro.h"

Scoutb�ro::Scoutb�ro()
{
	cData = nullptr;
	bSucheAktiv = false;
	iRangmin = 1;
	iKostenmitarbeiter = 400;
	iZeitversatz = rand() % 5 + 3;
	BerrechnungVoraussichtlicheZeit();
	eRang = static_cast<Rang>(rand()%2+iRangmin);
}

Scoutb�ro::Scoutb�ro(Data* data)
{
	cData=data;
	bSucheAktiv = false;
	iRangmin = 1;
	iKostenmitarbeiter = 400;
	iZeitversatz = rand() % 5 + 3;
	BerrechnungVoraussichtlicheZeit();
	eRang = static_cast<Rang>(rand() % 2 + iRangmin);
}

Scoutb�ro::~Scoutb�ro()
{
}

std::stringstream Scoutb�ro::SucheText()
{
	 std::stringstream ssText;
	 ssText << "Die Mitarbeiter des\nScoutb�ros suchen intensiv\nnach einem Geeignetem\nMitglied. Die Suche\ndauert voraussichtlich\nnoch " << getTimerstand();
	 return ssText;
}

void Scoutb�ro::startSuche()
{
	eRang = static_cast<Rang>(rand() % 2 + iRangmin);
	//Erzeugen eines EM Objektes
	switch (eRang)
	{
	case S:
	{
		iZeitversatz = rand() % 20 + 7;
		BerrechnungVoraussichtlicheZeit();
	}break;
	case A:
	{
		iZeitversatz = rand() % 20 + 9;
		BerrechnungVoraussichtlicheZeit();
	}break;
	case B:
	{
		iZeitversatz = rand() % 20 + 11;
		BerrechnungVoraussichtlicheZeit();
	}break;
	case C:
	{
		iZeitversatz = rand() % 20 + 13;
		BerrechnungVoraussichtlicheZeit();
	}break;
	case D:
	{
		iZeitversatz = rand() % 20 + 15;
		BerrechnungVoraussichtlicheZeit();
	}break;
	case E:
	{
		iZeitversatz = rand() % 20 + 17;
		BerrechnungVoraussichtlicheZeit();
	}break;
	case F:
	{
		iZeitversatz = rand() % 20 + 19;
		BerrechnungVoraussichtlicheZeit();
	}break;
	}
	cData->getKacheln(12).neuesBild(SucheText().str(), 160, 1, 1, 1);
	bSucheAktiv = true;
}

void Scoutb�ro::aktSuche()
{
	cData->getKacheln(12).changeText(SucheText().str(), 160);
}

void Scoutb�ro::EndeSuche()
{
	std::stringstream ssText;
	ssText << "Starke:Test\nAffinit�t: Test\nProzentualer Anteil: Test";
	cData->getKacheln(12).neuesBild(ssText.str(), 160, 1, 1, 1);
	cData->getKacheln(12).addButten(35, 400, 200, 30, 5, "Annehmen", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
	cData->getKacheln(12).addButten(35, 450, 200, 30, 6, "Ablehnen", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);

	cData->setiKontostand(cData->getiKontostand() - (eRang * iKostenmitarbeiter * (iVoraussichtlicheZeit + iZeitversatz)));

	bSucheAktiv = false;	// Auf False setzen damit nicht der andere Text ausgegeben wird von aktAusbildung

	cData->getAnimationen().startBenarichtigung(true);
}

void Scoutb�ro::Annehmen()
{
	// EM dauerhaft in Data speichern
	cData->getKacheln(12).neuesBild("Error in Annehmen", 160, 1, 1, 1);
	aktstd();
	cData->getKacheln(12).addButten(35, 450, 200, 30, 1, "Starten", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
}

void Scoutb�ro::Ablehnen()
{
	//EM = nullptr
	cData->getKacheln(12).neuesBild("Error in Ablehnen", 160, 1, 1, 1);
	aktstd();
	cData->getKacheln(12).addButten(35, 450, 200, 30, 1, "Starten", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
}

void Scoutb�ro::upgrade()
{
}

void Scoutb�ro::UpgradeGeschwindikeit()
{
	if (cData->getiKontostand() > cData->getfUpgradeKosten(1, 0) && cData->getScoutb�roGeschwindikeitsfaktor() >= 0.1)	// �berpr�fen ob die Ausbildung bezahlt werden kann
	{
		cData->setScoutb�roGeschwindikeitsFaktor(cData->getScoutb�roGeschwindikeitsfaktor() - 0.05);		// Durchf�ren der Verbesserung 

		cData->setiKontostand(cData->getiKontostand() - cData->getfUpgradeKosten(1, 0));					// Abziehn der Verbesserungskosten
		cData->setfUpgradeKosten(1, 0, cData->getfUpgradeKosten(1, 0) * 1.2);								// Speichern der neuen Verbesserungskosten

		if (!bSucheAktiv)	// �berpr�ft ob ein Batilion ausgebildet wird, wenn ja wird die Anzeige und  Uhr nicht aktualiesiert da dies zu Anzeigebugs f�hrt
		{
			BerrechnungVoraussichtlicheZeit();
			aktstd();
		}

		if (cData->getScoutb�roGeschwindikeitsfaktor() < 0.10)
		{
			// Ausgabe des neuen Textes
			std::stringstream ss;
			ss << "Die Maximale Stufe\nw�rde erreicht.\nSie k�nnen diesen\nPrarameter nicht mehr\noprimieren";
			cData->getKacheln(13).neuesBild(ss.str(), 350, 1, 1, 1);
		}

		else
		{
			// Ausgabe des neuen Textes
			std::stringstream ss;
			ss << "Beschleunigt die\nAusbildungsdauer um 5%\nKosten:" << cData->getfUpgradeKosten(1, 0);
			cData->getKacheln(13).changeText(ss.str(), 350);
		}
	}
}

void Scoutb�ro::UpgradeRang()
{
	if (cData->getiKontostand() > cData->getfUpgradeKosten(1, 1) && iRangmin<6)								// �berpr�fen ob die Ausbildung bezahlt werden kann
	{
		iRangmin++;																							// Durchf�ren der Verbesserung 

		cData->setiKontostand(cData->getiKontostand() - cData->getfUpgradeKosten(1, 1));					// Abziehn der Verbesserungskosten
		cData->setfUpgradeKosten(1, 1, cData->getfUpgradeKosten(1, 0) * 1.2);								// Speichern der neuen Verbesserungskosten

		if (!bSucheAktiv)	// �berpr�ft ob ein Batilion ausgebildet wird, wenn ja wird die Anzeige und  Uhr nicht aktualiesiert da dies zu Anzeigebugs f�hrt
		{
			BerrechnungVoraussichtlicheZeit();
			aktstd();
		}

		if (iRangmin == 6)
		{
			// Ausgabe des neuen Textes
			std::stringstream ss;
			ss << "Die Maximale Stufe\nw�rde erreicht.\nSie k�nnen diesen\nPrarameter nicht mehr\noprimieren";
			cData->getKacheln(14).neuesBild(ss.str(), 350, 1, 1, 1);
		}

		else
		{
			// Ausgabe des neuen Textes
			std::stringstream ss;
			ss << "Das Scoutb�ro\nfindet Einzelkampfer die\neinen h�heren Rang\nund Potenzial habne\nKosten: " << cData->getfUpgradeKosten(1, 0);
			cData->getKacheln(14).changeText(ss.str(), 320);
		}
	}	
}

void Scoutb�ro::UpgradeKosten()
{
	if (cData->getiKontostand() > cData->getfUpgradeKosten(1, 2) && iKostenmitarbeiter > 10)	// �berpr�fen ob die Ausbildung bezahlt werden kann
	{
		iKostenmitarbeiter -= 10;																	// Durchf�ren der Verbesserung 

		cData->setiKontostand(cData->getiKontostand() - cData->getfUpgradeKosten(1, 2));			// Abziehn der Verbesserungskosten
		cData->setfUpgradeKosten(1, 2, cData->getfUpgradeKosten(1, 2) * 1.4);						// Speichern der neuen Verbesserungskosten		

		if (!bSucheAktiv)	// �berpr�ft ob ein EM gesucht wird, wenn ja wird die Anzeige und  Uhr nicht aktualiesiert da dies zu Anzeigebugs f�hrt
		{
			BerrechnungVoraussichtlicheZeit();
			aktstd();			
		}

		if (iKostenmitarbeiter == 10)
		{
			// Ausgabe des neuen Textes
			std::stringstream ss;
			ss << "Die Maximale Stufe\nw�rde erreicht.\nSie k�nnen diesen\nPrarameter nicht mehr\noprimieren";
			cData->getKacheln(15).neuesBild(ss.str(), 350, 1, 1, 1);
		}

		else
		{
			std::stringstream ss;
			ss << "Reduzierung der Kosten\nKosten: " << cData->getfUpgradeKosten(1, 2);
			cData->getKacheln(15).changeText(ss.str(), 350);
		}
	}
}

void Scoutb�ro::aktstd()
{
	std::stringstream ssText;
	ssText << "Einselk�mpfer Rekutieren\n(EM)\nEin EM bekommt\nein Teil der Finanzellen\nBehlohnung und hat\neine Affinit�t.\nDie Affinit�t erlaubt\ndie Ausstatung spezieller\nWaffen und bringt\nVorteile bei bestimmten\nAuftragen."; //\nSuchkosten: " << eRang * iKostenmitarbeiter * iVoraussichtlicheZeit << "\nVoraussichtliche dauer: " << iVoraussichtlicheZeit;
	cData->getKacheln(12).changeText(ssText.str(), 160);
}

void Scoutb�ro::BerrechnungVoraussichtlicheZeit()
{
	iVoraussichtlicheZeit = (iZeitversatz * eRang * cData->getScoutb�roGeschwindikeitsfaktor() * // Ermitteln der Zeit die Vorausichtlich f�r die Ausbildung gebraucht wird Unterberucksichtigung von der eines Faktors, der Gr��e, der Grundgeschwindikeit, der Bekanntheit
		((cData->getBekanntheit() < 1000) ? 3 : (cData->getBekanntheit() < 10000) ? 2 : 1));	 // Ermitteln der Bekanntheit und dem dadurch resultierendem Faktor

	neuerTimer(iVoraussichtlicheZeit);
}

void Scoutb�ro::updateTimer()
{
	aktTimer();									// akktualiesieren der Uhr

	if (getTimerstand() + iZeitversatz == 0&&bSucheAktiv)	// �berpr�fen ob die Zeit abgelaugen ist 
		EndeSuche();						// Beenden der Ausbildung, da die Ausbildung fertig ist 

	else if (bSucheAktiv)					// Aktualiesiern des Angezeigten Ausbildungs Fortschritts
		aktSuche();
}
