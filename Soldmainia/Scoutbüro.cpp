#include "Scoutbüro.h"

Scoutbüro::Scoutbüro()
{
	cData = nullptr;
	bSucheAktiv = false;
	iRangmin = 1;
	iKostenmitarbeiter = 400;
	iZeitversatz = rand() % 5 + 3;
	BerrechnungVoraussichtlicheZeit();
	eRang = static_cast<Rang>(rand()%2+iRangmin);
	iLevel[0] = iLevel[1] = iLevel[2] = 0;
}

Scoutbüro::Scoutbüro(Data* data)
{
	cData=data;
	bSucheAktiv = false;
	iRangmin = 1;
	iKostenmitarbeiter = 400;
	iZeitversatz = rand() % 5 + 3;
	BerrechnungVoraussichtlicheZeit();
	eRang = static_cast<Rang>(rand() % 2 + iRangmin);
	iLevel[0] = iLevel[1] = iLevel[2] = 0;
}

Scoutbüro::~Scoutbüro()
{
}

std::stringstream Scoutbüro::SucheText()
{
	 std::stringstream ssText;
	 ssText << "Die Mitarbeiter des\nScoutbüros suchen intensiv\nnach einem Geeignetem\nMitglied. Die Suche\ndauert voraussichtlich\nnoch " << getTimerstand();
	 return ssText;
}

void Scoutbüro::startSuche()
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
	cData->getKacheln(12).neuesBild(SucheText().str(), 300, 13, 30, 95);
	bSucheAktiv = true;

	cData->setiKontostand(cData->getiKontostand() - (eRang * iKostenmitarbeiter * (iVoraussichtlicheZeit + iZeitversatz)));
	std::stringstream ssText;
	ssText << -(cData->getiKontostand() - (eRang * iKostenmitarbeiter * (iVoraussichtlicheZeit + iZeitversatz))) << " Suchkosten";
	cData->getAnimationen().startBenarichtigung(false, ssText.str());
	ssText.clear();
}

void Scoutbüro::aktSuche()
{
	cData->getKacheln(12).changeText(SucheText().str(), 300);
}

void Scoutbüro::EndeSuche()
{
	std::stringstream ssText;
	ssText << "Starke:Test\nAffinität: Test\nProzentualer Anteil: Test";
	cData->getKacheln(12).neuesBild(ssText.str(), 160, 99, 1, 1);
	cData->getKacheln(12).addButten(35, 400, 200, 30, 5, "Annehmen", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255,150,0), sf::Color::White, cData->getKacheln(12).getSize().x, cData->getKacheln(12).getSize().y);
	cData->getKacheln(12).addButten(35, 450, 200, 30, 6, "Ablehnen", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255,150,0), sf::Color::White, cData->getKacheln(12).getSize().x, cData->getKacheln(12).getSize().y);

	
	bSucheAktiv = false;	// Auf False setzen damit nicht der andere Text ausgegeben wird von aktAusbildung
	cData->getAnimationen().startBenarichtigung(true, "Suche erfolgreich Abgeschlossen");
	ssText.clear();
}

void Scoutbüro::Annehmen()
{
	// EM dauerhaft in Data speichern
	cData->getKacheln(12).neuesBild("Error in Annehmen", 160, 99, 1, 1);
	aktstd();
	cData->getKacheln(12).addButten(35, 450, 200, 30, 1, "Starten", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, cData->getKacheln(12).getSize().x, cData->getKacheln(12).getSize().y);
	cData->getAnimationen().startBenarichtigung(true, "EM Angenomen");
}

void Scoutbüro::Ablehnen()
{
	//EM = nullptr
	cData->getKacheln(12).neuesBild("Error in Ablehnen", 160, 99, 1, 1);
	aktstd();
	cData->getKacheln(12).addButten(35, 450, 200, 30, 1, "Starten", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, cData->getKacheln(12).getSize().x, cData->getKacheln(12).getSize().y);
	cData->getAnimationen().startBenarichtigung(false, "EM Abgelehnt");
	bSucheAktiv = false;
}

void Scoutbüro::upgrade()
{
}

void Scoutbüro::UpgradeGeschwindikeit()
{
	if (cData->getiKontostand() > cData->getfUpgradeKosten(1, 0) && cData->getScoutbüroGeschwindikeitsfaktor() >= 0.05)	// überprüfen ob die Ausbildung bezahlt werden kann
	{
		cData->setScoutbüroGeschwindikeitsFaktor(cData->getScoutbüroGeschwindikeitsfaktor() * 0.95);		// Durchfüren der Verbesserung 

		iLevel[0]++;

		std::stringstream ssk;
		ssk << -(cData->getfUpgradeKosten(1, 0));
		cData->getAnimationen().startBenarichtigung(false, ssk.str());
		ssk.clear();
		
		cData->setiKontostand(cData->getiKontostand() - cData->getfUpgradeKosten(1, 0));					// Abziehn der Verbesserungskosten
		cData->setfUpgradeKosten(1, 0, cData->getfUpgradeKosten(1, 0) * ((iLevel[0] < 15) ? 2,5 : ((iLevel[0] < 34) ? 1,4 : 1,2)));								// Speichern der neuen Verbesserungskosten
		
		cData->getAnimationen().startUpgradeAnimation(2, cData->getBreite(), cData->getBreite());

		std::stringstream ss;
		if (!bSucheAktiv)	// überprüft ob ein Batilion ausgebildet wird, wenn ja wird die Anzeige und  Uhr nicht aktualiesiert da dies zu Anzeigebugs führt
		{
			BerrechnungVoraussichtlicheZeit();
			aktstd();
		}

		if (cData->getScoutbüroGeschwindikeitsfaktor() < 0.10)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nwürde erreicht.\nSie können diesen\nPrarameter nicht mehr\noprimieren";
			cData->getKacheln(13).neuesBild(ss.str(), 350, 1, 285 , 95);
		}

		else
		{
			// Ausgabe des neuen Textes
			ss << "Beschleunigt die\nAusbildungsdauer um 5%\nKosten:" << cData->getfUpgradeKosten(1, 0) << "\nLevel: " << iLevel[0] << "/" << 58;
			cData->getKacheln(13).changeText(ss.str(), 350);
		}

		ss.clear();
	}
}

void Scoutbüro::UpgradeRang()
{
	if (cData->getiKontostand() > cData->getfUpgradeKosten(1, 1) && iRangmin<6)								// überprüfen ob die Ausbildung bezahlt werden kann
	{
		iRangmin++;																							// Durchfüren der Verbesserung 

		iLevel[1]++;

		std::stringstream ssk;
		ssk << -(cData->getfUpgradeKosten(1, 1));
		cData->getAnimationen().startBenarichtigung(false, ssk.str());
		ssk.clear();

		cData->setiKontostand(cData->getiKontostand() - cData->getfUpgradeKosten(1, 1));					// Abziehn der Verbesserungskosten
		cData->setfUpgradeKosten(1, 1, cData->getfUpgradeKosten(1, 1) * 1.6);								// Speichern der neuen Verbesserungskosten

		cData->getAnimationen().startUpgradeAnimation(3, cData->getBreite(), cData->getBreite());

		std::stringstream ss;
		if (!bSucheAktiv)	// überprüft ob ein Batilion ausgebildet wird, wenn ja wird die Anzeige und  Uhr nicht aktualiesiert da dies zu Anzeigebugs führt
		{
			BerrechnungVoraussichtlicheZeit();
			aktstd();
		}

		if (iRangmin == 6)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nwürde erreicht.\nSie können diesen\nPrarameter nicht mehr\noprimieren";
			cData->getKacheln(14).neuesBild(ss.str(), 350, 1, 535, 95);
		}

		else
		{
			// Ausgabe des neuen Textes
			ss << "Das Scoutbüro\nfindet Einzelkampfer die\neinen höheren Rang\nund Potenzial habne\nKosten: " << cData->getfUpgradeKosten(1, 1) << "\nLevel: " << iLevel[1] << "/" << 6;
			cData->getKacheln(14).changeText(ss.str(), 320);
		}

		ss.clear();
	}	
}

void Scoutbüro::UpgradeKosten()
{
	if (cData->getiKontostand() > cData->getfUpgradeKosten(1, 2) && iKostenmitarbeiter > 10)	// überprüfen ob die Ausbildung bezahlt werden kann
	{
		iKostenmitarbeiter -= 10;																	// Durchfüren der Verbesserung 

		iLevel[2]++;

		std::stringstream ssk;
		ssk << -(cData->getfUpgradeKosten(1, 2));
		cData->getAnimationen().startBenarichtigung(false, ssk.str());
		ssk.clear();

		cData->setiKontostand(cData->getiKontostand() - cData->getfUpgradeKosten(1, 2));			// Abziehn der Verbesserungskosten
		cData->setfUpgradeKosten(1, 2, cData->getfUpgradeKosten(1, 2) * 1.4);						// Speichern der neuen Verbesserungskosten	

		cData->getAnimationen().startUpgradeAnimation(4, cData->getBreite(), cData->getBreite());

		std::stringstream ss;
		if (!bSucheAktiv)	// überprüft ob ein EM gesucht wird, wenn ja wird die Anzeige und  Uhr nicht aktualiesiert da dies zu Anzeigebugs führt
		{
			BerrechnungVoraussichtlicheZeit();
			aktstd();			
		}

		if (iKostenmitarbeiter == 10)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nwürde erreicht.\nSie können diesen\nPrarameter nicht mehr\noprimieren";
			cData->getKacheln(15).neuesBild(ss.str(), 350, 1, 785, 95);
		}

		else
		{
			ss << "Reduzierung der Kosten\nKosten: " << cData->getfUpgradeKosten(1, 2) << "\nLevel: " << iLevel[2]<<"/" << 40;
			cData->getKacheln(15).changeText(ss.str(), 350);
		}

		ss.clear();
	}
}

void Scoutbüro::aktstd()
{
	std::stringstream ssText;
	ssText << "Einselkämpfer Rekutieren\n(EM)\nEin EM bekommt\nein Teil der Finanzellen\nBehlohnung und hat\neine Affinität.\nDie Affinität erlaubt\ndie Ausstatung spezieller\nWaffen und bringt\nVorteile bei bestimmten\nAuftragen."; //\nSuchkosten: " << eRang * iKostenmitarbeiter * iVoraussichtlicheZeit << "\nVoraussichtliche dauer: " << iVoraussichtlicheZeit;
	cData->getKacheln(12).changeText(ssText.str(), 200);
	ssText.clear();
}

void Scoutbüro::BerrechnungVoraussichtlicheZeit()
{
	iVoraussichtlicheZeit = (iZeitversatz * eRang * cData->getScoutbüroGeschwindikeitsfaktor() * // Ermitteln der Zeit die Vorausichtlich für die Ausbildung gebraucht wird Unterberucksichtigung von der eines Faktors, der Größe, der Grundgeschwindikeit, der Bekanntheit
		((cData->getBekanntheit() < 1000) ? 3 : (cData->getBekanntheit() < 10000) ? 2 : 1));	 // Ermitteln der Bekanntheit und dem dadurch resultierendem Faktor

	neuerTimer(iVoraussichtlicheZeit);
}

void Scoutbüro::updateTimer()
{
	aktTimer();									// akktualiesieren der Uhr

	if (getTimerstand() + iZeitversatz == 0&&bSucheAktiv)	// überprüfen ob die Zeit abgelaugen ist 
		EndeSuche();						// Beenden der Ausbildung, da die Ausbildung fertig ist 

	else if (bSucheAktiv)					// Aktualiesiern des Angezeigten Ausbildungs Fortschritts
		aktSuche();
}
