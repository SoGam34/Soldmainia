#include "Batilion_Ausbildungszentrum.h"

Batillion_Ausbildungszentrum::Batillion_Ausbildungszentrum(
		std::shared_ptr<Data> data) :
		Gebaeude(data, 70, 10), Batillionsgroesse(10), Grundstaerke(10)
{

}

Batillion_Ausbildungszentrum::~Batillion_Ausbildungszentrum()
{
}

unsigned int Batillion_Ausbildungszentrum::getGebaeudeAusfuhrungskosten() const
{
	return AusfuhrungsKostenFaktor * (VoraussichtlicheZeit + Zeitversatz);
}

const std::stringstream Batillion_Ausbildungszentrum::getGebaudeAktivText() const
{
	// Der Text der warend der Ausbildung angezeigt wird 
	std::stringstream ssText;
	ssText << "Ausbildung eines neuen \nBatillions ist im Gang.\n"
			<< "Das Batillion wird aus\n" << Batillionsgroesse
			<< " Mitgliedern bestehen.\n" << "Die Ausbildung wird in\n"
			<< getTimerstand() << " Tagen vorausichtlich\nfertig sein.";
	return ssText;
}

void Batillion_Ausbildungszentrum::erhoheEinheitsGrosse()
{
	// Erhoht die Gesamtanzahl der Soldaten in dem Batillion und aktualiesiert die Ausgabe
	Batillionsgroesse += 1;
	GebaeudeEinflussZeitFaktor = Batillionsgroesse;
	berrechnungVoraussichtlicheZeit();
	aktualisierenInformationsText();
}

void Batillion_Ausbildungszentrum::reduziereEinheitsGrosse()
{
	// Reduziert die Gesamtanzahl der Soldaten in dem Batillion und aktualiesiert die Ausgabe
	Batillionsgroesse -= 1;
	GebaeudeEinflussZeitFaktor = Batillionsgroesse;
	berrechnungVoraussichtlicheZeit();
	aktualisierenInformationsText();
}

void Batillion_Ausbildungszentrum::beendenDerAusfuhrung()
{/*
	Daten->getKacheln(8).neueAnzeige(
			"Die Ausblidung ist\nbeendet, wie wollen\nsie das Batiliion\nnennen?",
			100, 99, 1, 1);	// Akktualiesieren des Textes

	//cData->getKacheln(8).addTextfeld(sf::Color::Black, cData->getFont(), sf::Vector2f(40, 200));
	Daten->getKacheln(8).ButtonHinzufuegen(35, 350, 200, 30, 5,
			"Namen Bestehtigen", *Daten->getFont(), sf::Color::Black,
			sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White,
			Data->getKacheln(8).getGroese().x,
			Data->getKacheln(8).getGroese().y);
	ProzessAktiv = false;// Auf False setzen damit nicht der andere Text ausgegeben wird von aktAusbildung
	//Generierung eines Batillions
	//Daten->getAnimationen().startBenarichtigung(true,"Ausbildung Batillion beendet");	TODO UI Animation*/
}

void Batillion_Ausbildungszentrum::vorbereiten_neueAusbildung()
{
	//neues Kachel Bild
	Zeitversatz = rand() % 5 + 3;// Berechnung der Ausbildungsdauer des n�chsten Batillions
	berrechnungVoraussichtlicheZeit();

	std::stringstream ssText;			// Der Text der Angezeigt werden soll
	ssText << "Neues Batillion ausbilden\nGroesse: " << Batillionsgroesse
			<< "\nKampfkraft: " << Batillionsgroesse * 10 * Grundstaerke
			<< "\nKosten: " << AusfuhrungsKostenFaktor * VoraussichtlicheZeit
			<< "\nVoraussichtlich fertig in: " << VoraussichtlicheZeit;

	/*Daten->getKacheln(8).neueAnzeige(ssText.str(), 200, 99, 1, 1);// Akktualiesieren des Textes
	// Hinzuf�gen aller Notiger Buttens 
	Daten->getKacheln(8).ButtonHinzufuegen(35, 450, 200, 30, 1, "Starten",
			*Daten->getFont(), sf::Color::Black, sf::Color(100, 100, 100),
			sf::Color(255, 150, 0), sf::Color::White,
			Data->getKacheln(8).getGroese().x,
			Data->getKacheln(8).getGroese().y);
	Daten->getKacheln(8).ButtonHinzufuegen(35, 350, 200, 30, 11,
			"Mehr Mitglieder", *Daten->getFont(), sf::Color::Black,
			sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White,
			Data->getKacheln(8).getGroese().x,
			Data->getKacheln(8).getGroese().y);
	Daten->getKacheln(8).ButtonHinzufuegen(35, 400, 200, 30, 12,
			"Weniger Mitglieder", *Daten->getFont(), sf::Color::Black,
			sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White,
			Data->getKacheln(8).getGroese().x,
			Data->getKacheln(8).getGroese().y);*/
}

inline void Batillion_Ausbildungszentrum::aktualisierenInformationsText()
{
	//Aktualieseiren der Anzeige wie das n�chste Batillion ausehen wird 
	std::stringstream ssText;
	ssText << "Neues Batillion ausbilden\nGroesse: " << Batillionsgroesse
			<< "\nKampfkraft: " << Batillionsgroesse * 10 * Grundstaerke
			<< "\nKosten: " << AusfuhrungsKostenFaktor * VoraussichtlicheZeit
			<< "\nVoraussichtlich fertig in: " << VoraussichtlicheZeit;

	//Daten->getKacheln(8).TextAendern(ssText.str(), 200);
}

void Batillion_Ausbildungszentrum::erhohenDerGrundstarke()
{
	if (Daten->getKontostand() > UpgradeKosten[1] && Grundstaerke < 25)	// �berpr�fen ob die Ausbildung bezahlt werden kann
	{
		Grundstaerke += 1;						// Durchf�ren der Verbesserung

		std::stringstream ssk;
		ssk << -UpgradeKosten[1];
		//Daten->getAnimationen().startBenarichtigung(false, ssk.str());	TODO UI Animation
		ssk.clear();

		Daten->abziehnVonKontostand(UpgradeKosten[1]);// Abziehn der Verbesserungskosten
		UpgradeKosten[1] *= 1.6;	// Speichern der neuen Verbesserungskosten

		//Daten->setKontostand(Daten->getKontostand() - UpgradeKosten[1]);			// Abziehn der Verbesserungskosten
		//fUpgradeKosten[1]= fUpgradeKosten[1] * ((iLevel[1] < 9) ? cData->getUpgradeFaktorScoutbuero(2, 0) : (iLevel[1] < 17) ? cData->getUpgradeFaktorScoutbuero(2, 1) : cData->getUpgradeFaktorScoutbuero(2, 2)));					// Speichern der neuen Verbesserungskosten

		//Daten->getAnimationen().startUpgradeAnimation(3, Daten->getBreite(), Daten->getHohe());	TODO UI Animation

		std::stringstream ss;
		if (!ProzessAktiv)// �berpr�ft ob ein Batillion ausgebildet wird, wenn ja wird die Anzeige und  Uhr nicht aktualiesiert da dies zu Anzeigebugs f�hrt
		{
			aktualisierenInformationsText();
			berrechnungVoraussichtlicheZeit();
		}

		if (Grundstaerke > 24)
		{
			// Ausgabe des neuen Textes
			ss
					<< "Die Maximale Stufe\nwuerde erreicht.\nSie koennen diesen\nPrarameter nicht mehr\noprimieren";
			//Daten->getKacheln(10).neueAnzeige(ss.str(), 350, 1, 535, 95);
		}

		else
		{
			// Ausgabe des neuen Textes
			ss << "Erhoehung der Grundstaerke\nKosten: " << UpgradeKosten[1];
			//Daten->getKacheln(10).TextAendern(ss.str(), 350);
		}

		ss.clear();
	}
}
