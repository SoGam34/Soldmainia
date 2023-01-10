#include "PreHeader.h"
#include "Batilion_Ausbildungszentrum.h"

Batilion_Ausbildungszentrum::Batilion_Ausbildungszentrum()
{
	cData = nullptr;					// intiltilisieren mit nullptr zur prevention von Schaden die angerichtet werden koennten
	bAusbildungAktiv = false;			// Auf False setzen, da keine Aubildung statt findet
	
	iZeitversatz = rand() % 5 + 3;		// Festlegen des neuen Zeitversatzes mit dem 
	BerrechnungVoraussichtlicheZeit();	// hier gearbeitet wird 
}

Batilion_Ausbildungszentrum::Batilion_Ausbildungszentrum(Data* data)
{
	cData = data;						// intitlaiesieren von data 
	bAusbildungAktiv = false;			// Auf False setzen, da keine Aubildung statt findet
	
	iZeitversatz = rand() % 5 + 3;		// Festlegen des neuen Zeitversatzes mit dem 
	BerrechnungVoraussichtlicheZeit();	// hier gearbeitet wird 

	iLevel[0] = iLevel[1] = iLevel[2] = 0;
}

Batilion_Ausbildungszentrum::~Batilion_Ausbildungszentrum()
{

}

void Batilion_Ausbildungszentrum::updateTimer()
{
	aktTimer();									// akktualiesieren der Uhr

	if (getTimerstand() + iZeitversatz == 0&&bAusbildungAktiv)	// ueberpruefen ob die Zeit abgelaugen ist 
		Name();						// Beenden der Ausbildung, da die Ausbildung fertig ist 

	else if (bAusbildungAktiv)					// Aktualiesiern des Angezeigten Ausbildungs Fortschritts
		aktAusbildung();
}

std::stringstream Batilion_Ausbildungszentrum::AusbildungsText()
{
	// Der Text der warend der Ausbildung angezeigt wird 
	std::stringstream ssText;
	ssText << "Ausbildung eines neuen \nBatilions ist im Gang.\n"
		<< "Das Batilion wird aus\n" << cData->getBatilionsgroese() << " Mitgliedern bestehen.\n"
		<< "Die Ausbildung wird in\n" << getTimerstand() << " Tagen vorausichtlich\nfertig sein.";
	return ssText;
}

void Batilion_Ausbildungszentrum::startAusbildung()
{
	if (cData->getiKontostand() > cData->getKostenProKopf() * (iVoraussichtlicheZeit+iZeitversatz)) // ueberpruefen ob die Ausbildung bezahlt werden kann
	{
		std::stringstream ss;
		ss << -(cData->getKostenProKopf() * iVoraussichtlicheZeit);
		cData->getAnimationen().startBenarichtigung(false, ss.str());
		ss.clear();

		neuerTimer(iVoraussichtlicheZeit);																	// Start des Timers	
		cData->setiKontostand(cData->getiKontostand() - cData->getKostenProKopf() * iVoraussichtlicheZeit);	// Abziehn der gesamten Ausbildungskosten
		bAusbildungAktiv = true;																			// Auf true gesetzt damit der Ausbildungsvortschrit angezietgt wird 
		cData->getKacheln(8).neuesBild(AusbildungsText().str(), 300, 12, 30, 95);	//neues Kachel Bild	
		
	}

	else
	{
		cData->getAnimationen().KeinGeld(cData->getWindowSize(), cData->getFont());
	}
}

void Batilion_Ausbildungszentrum::aktAusbildung()
{
	cData->getKacheln(8).changeText(AusbildungsText().str(), 300);	//neues Kachel Bild
}

void Batilion_Ausbildungszentrum::Name()
{
	cData->getKacheln(8).neuesBild("Die Ausblidung ist\nbeendet, wie wollen\nsie das Batiliion\nnennen?", 100, 99, 1, 1);	// Akktualiesieren des Textes 

	cData->getKacheln(8).addTextfeld(sf::Color::Black, cData->getFont(), sf::Vector2f(40, 200));
	cData->getKacheln(8).addButten(35, 350, 200, 30, 5, "Namen Bestehtigen", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, cData->getKacheln(8).getSize().x, cData->getKacheln(8).getSize().y);
	bAusbildungAktiv = false;	// Auf False setzen damit nicht der andere Text ausgegeben wird von aktAusbildung

	std::stringstream ss;
	ss << "Ausbildung Batilion beendet";
	cData->getAnimationen().startBenarichtigung(true, ss.str());
	ss.clear();
}
void Batilion_Ausbildungszentrum::EndeAusbildung()
{
	//Generierung eines Batilions
	//neues Kachel Bild
	iZeitversatz = rand() % 5 + 3;		// Berechnung der Ausbildungsdauer des naechsten Batilions 
	BerrechnungVoraussichtlicheZeit();

	std::stringstream ssText;			// Der Text der Angezeigt werden soll
	ssText << "Neues Batilion Ausbilden\nGroese: " << cData->getBatilionsgroese() << "\nKampfkraft: " << cData->getBatilionsgroese() * 10 * cData->getGrundstaerke() << "\nKosten: " << cData->getKostenProKopf() * iVoraussichtlicheZeit << "\nVorausichtlich fertig in: " << iVoraussichtlicheZeit;

	cData->getKacheln(8).neuesBild(ssText.str(), 200, 99, 1, 1);	// Akktualiesieren des Textes 
	// Hinzufuegen aller Notiger Buttens 
	cData->getKacheln(8).addButten(35, 450, 200, 30, 1, "Starten", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, cData->getKacheln(8).getSize().x, cData->getKacheln(8).getSize().y);
	cData->getKacheln(8).addButten(35, 350, 200, 30, 11, "Mehr Mitglieder", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, cData->getKacheln(8).getSize().x, cData->getKacheln(8).getSize().y);
	cData->getKacheln(8).addButten(35, 400, 200, 30, 12, "Weniger Mitglieder", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, cData->getKacheln(8).getSize().x, cData->getKacheln(8).getSize().y);
}

void Batilion_Ausbildungszentrum::aktstd()
{
	//Aktualieseiren der Anzeige wie das naechste Batilion ausehen wird 
	std::stringstream ssText;
	ssText << "Neues Batilion Ausbilden\nGroese: " << cData->getBatilionsgroese() << "\nKampfkraft: " << cData->getBatilionsgroese() * 10* cData->getGrundstaerke() << "\nKosten: " << cData->getKostenProKopf() * iVoraussichtlicheZeit << "\nVorausichtlich fertig in: " << iVoraussichtlicheZeit;
	cData->getKacheln(8).changeText(ssText.str(), 200);
	ssText.clear();
}

void Batilion_Ausbildungszentrum::AnzahlErhohen()
{
	// Erhoht die Gesamtanzahl der Soldaten in dem Batilion und aktualiesiert die Ausgabe
	cData->setBatilionsgroese(cData->getBatilionsgroese() + 1);
	BerrechnungVoraussichtlicheZeit();
	aktstd();
}

void Batilion_Ausbildungszentrum::AnzahlReduzieren()
{
	// Reduziert die Gesamtanzahl der Soldaten in dem Batilion und aktualiesiert die Ausgabe
	cData->setBatilionsgroese(cData->getBatilionsgroese() - 1);
	BerrechnungVoraussichtlicheZeit();
	aktstd();
}

void Batilion_Ausbildungszentrum::UpgradeGeschwindikeit()
{
	if (cData->getiKontostand() > cData->getfUpgradeKosten(0, 0) && cData->getBatilionGeschwindikeitsfaktor() >= 0.05)	// ueberpruefen ob die Ausbildung bezahlt werden kann
	{
		cData->setBatilionGeschwindikeitsFaktor(cData->getBatilionGeschwindikeitsfaktor() * 0.95);							// Durchfueren der Verbesserung 

		std::stringstream ssk;
		ssk << -(cData->getfUpgradeKosten(0, 0));
		cData->getAnimationen().startBenarichtigung(false, ssk.str());
		ssk.clear();

		iLevel[0]++;

		cData->setiKontostand(cData->getiKontostand() - cData->getfUpgradeKosten(0, 0));					// Abziehn der Verbesserungskosten
		cData->setfUpgradeKosten(0, 0, cData->getfUpgradeKosten(0, 0) * ((iLevel[0] < 15) ? cData->getUpgradeFaktorScoutbuero(0, 0) : (iLevel[0] < 35) ? cData->getUpgradeFaktorScoutbuero(0, 1) : cData->getUpgradeFaktorScoutbuero(0, 2)));								// Speichern der neuen Verbesserungskosten

		cData->getAnimationen().startUpgradeAnimation(2, cData->getBreite(), cData->getHohe());

		std::stringstream ss;
		if (!bAusbildungAktiv)	// ueberprueft ob ein Batilion ausgebildet wird, wenn ja wird die Anzeige und  Uhr nicht aktualiesiert da dies zu Anzeigebugs fuehrt
		{
			aktstd();
			BerrechnungVoraussichtlicheZeit();
		}

		if (cData->getBatilionGeschwindikeitsfaktor() < 0.1)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nwuerde erreicht.\nSie koennen diesen\nPrarameter nicht mehr\noprimieren";
			cData->getKacheln(9).neuesBild(ss.str(), 350, 1, 285, 95);
		}

		else
		{
			// Ausgabe des neuen Textes
			ss << "Beschleunigt die\nAusbildungsdauer um 5%\nKosten: " << cData->getfUpgradeKosten(0, 0)<<"\nLevel: "<<iLevel[0]<<"/ 58";
			cData->getKacheln(9).changeText(ss.str(), 350);
		}

		ss.clear();
	}

	else
	{
		cData->getAnimationen().KeinGeld(cData->getWindowSize(), cData->getFont());
	}
}

void Batilion_Ausbildungszentrum::UpgradeGrundstarke()
{
	if (cData->getiKontostand() > cData->getfUpgradeKosten(0, 1) && cData->getGrundstaerke() < 25)	// ueberpruefen ob die Ausbildung bezahlt werden kann
	{
		cData->setGrundstaerke(cData->getGrundstaerke() + 1);											// Durchfueren der Verbesserung 

		std::stringstream ssk;
		ssk << -(cData->getfUpgradeKosten(0, 1));
		cData->getAnimationen().startBenarichtigung(false, ssk.str());
		ssk.clear();

		iLevel[1]++;

		cData->setiKontostand(cData->getiKontostand() - cData->getfUpgradeKosten(0, 1));			// Abziehn der Verbesserungskosten
		cData->setfUpgradeKosten(0, 1, cData->getfUpgradeKosten(0, 1) * ((iLevel[1] < 9) ? cData->getUpgradeFaktorScoutbuero(2, 0) : (iLevel[1] < 17) ? cData->getUpgradeFaktorScoutbuero(2, 1) : cData->getUpgradeFaktorScoutbuero(2, 2)));					// Speichern der neuen Verbesserungskosten

		cData->getAnimationen().startUpgradeAnimation(3, cData->getBreite(), cData->getHohe());
		
		std::stringstream ss;
		if (!bAusbildungAktiv)	// ueberprueft ob ein Batilion ausgebildet wird, wenn ja wird die Anzeige und  Uhr nicht aktualiesiert da dies zu Anzeigebugs fuehrt
		{
			aktstd();
			BerrechnungVoraussichtlicheZeit();
		}

		if (cData->getGrundstaerke() > 24)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nwuerde erreicht.\nSie koennen diesen\nPrarameter nicht mehr\noprimieren";
			cData->getKacheln(10).neuesBild(ss.str(), 350, 1, 535, 95);
		}

		else
		{
			// Ausgabe des neuen Textes
			ss << "Erhoung der Grundstaerke\nKosten: " << cData->getfUpgradeKosten(0, 1) << "\nLevel: " << iLevel[2] << "/" << 16;
			cData->getKacheln(10).changeText(ss.str(), 350);
		}

		ss.clear();
	}

	else
	{
		cData->getAnimationen().KeinGeld(cData->getWindowSize(), cData->getFont());
	}
}

void Batilion_Ausbildungszentrum::UpgradeKosten()
{
	if (cData->getiKontostand() > cData->getfUpgradeKosten(0, 2) && cData->getKostenProKopf() >= 10)	// ueberpruefen ob die Ausbildung bezahlt werden kann
	{
		cData->setKostenProKopf(cData->getKostenProKopf() - 5);										// Durchfueren der Verbesserung 

		std::stringstream ssk;
		ssk << -(cData->getfUpgradeKosten(0, 2));
		cData->getAnimationen().startBenarichtigung(false, ssk.str());
		ssk.clear();

		iLevel[2]++;

		cData->setiKontostand(cData->getiKontostand() - cData->getfUpgradeKosten(0, 2));			// Abziehn der Verbesserungskosten
		cData->setfUpgradeKosten(0, 2, cData->getfUpgradeKosten(0, 2) * ((iLevel[2] < 9) ? cData->getUpgradeFaktorScoutbuero(0, 0) : (iLevel[2] < 13) ? cData->getUpgradeFaktorScoutbuero(0, 1) : cData->getUpgradeFaktorScoutbuero(0, 2)));						// Speichern der neuen Verbesserungskosten

		cData->getAnimationen().startUpgradeAnimation(4, cData->getBreite(), cData->getHohe());

		std::stringstream ss;
		if (!bAusbildungAktiv)	// ueberprueft ob ein Batilion ausgebildet wird, wenn ja wird die Anzeige und  Uhr nicht aktualiesiert da dies zu Anzeigebugs fuehrt
		{
			aktstd();
			BerrechnungVoraussichtlicheZeit();
		}

		if (cData->getKostenProKopf() < 10)
		{
			// Ausgabe des neuen Textes
			ss << "Die Maximale Stufe\nwuerde erreicht.\nSie koennen diesen\nPrarameter nicht mehr\noprimieren";
			cData->getKacheln(11).neuesBild(ss.str(), 350, 1, 785, 95);
		}

		else
		{
			ss << "Reduzierung der Kosten\nKosten: " << cData->getfUpgradeKosten(0, 2) << "\nLevel: " << iLevel[2] << "/ 14";
			cData->getKacheln(11).changeText(ss.str(), 350);
		}

		ss.clear();
	}

	else
	{
		cData->getAnimationen().KeinGeld(cData->getWindowSize(), cData->getFont());
	}
}

void Batilion_Ausbildungszentrum::upgrade()
{
}

void Batilion_Ausbildungszentrum::BerrechnungVoraussichtlicheZeit()
{
	iVoraussichtlicheZeit = (iZeitversatz * cData->getBatilionsgroese() * cData->getBatilionGeschwindikeitsfaktor() * // Ermitteln der Zeit die Vorausichtlich fuer die Ausbildung gebraucht wird Unterberucksichtigung von der eines Faktors, der Groese, der Grundgeschwindikeit, der Bekanntheit
		((cData->getBekanntheit() < 1000) ? 3 : (cData->getBekanntheit() < 10000) ? 2 : 1));				 // Ermitteln der Bekanntheit und dem dadurch resultierendem Faktor
	
	neuerTimer(iVoraussichtlicheZeit);																		 // Satrten der Uhr mit der neuen Zeit
}
