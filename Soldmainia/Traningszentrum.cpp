#include "Traningszentrum.h"

Traningszentrum::Traningszentrum(Data*data) : Gebaeude(data, 16,100,1), Auswahl(data)
{
}

Traningszentrum::~Traningszentrum()
{
}

std::stringstream Traningszentrum::ProzessText()
{
	// Der Text der warend des TRainings angezeigt wird 
	std::stringstream ssText;
	ssText << "Die Einheit "<<sName<<"\nwird gerade Trainiert\nDas Training ist\nvorausicht in "<<iVoraussichtlicheZeit<<"\nTagen abgeschloﬂen";
	return ssText;
}

int Traningszentrum::ProzessKosten()
{
	return iKostenFaktor*(iVoraussichtlicheZeit+iZeitversatz)*cData->getEinheiten()[sName].Groﬂe;
}

void Traningszentrum::EndeProzess()
{
	//neues Kachel Bild
	iZeitversatz = rand() % 5 + 3;		// Berechnung der Ausbildungsdauer des n‰chsten Batilions 
	BerrechnungVoraussichtlicheZeit();

	std::stringstream ssText;			// Der Text der Angezeigt werden soll
	ssText << "Neue Einheit Trainieren\nDie Einheit erhalt\nErfahrungspunkte was sie\nStarker macht und\ndie Erfolgsraten in\nEinsatzen verbessert.\nDei Menge der\nErfahrungspunkte hangt von\nder Dauer ab";

	cData->getKacheln(16).neuesBild(ssText.str(), 200, 99, 1, 1);	// Akktualiesieren des Textes 
	//// Hinzuf¸gen aller Notiger Buttens 
	cData->getKacheln(16).addButten(35, 450, 200, 30, 5, "Lange Tranings Einheit", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
	cData->getKacheln(16).addButten(35, 350, 200, 30, 6, "Kurze Trainings Einheit", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
	cData->getKacheln(16).addButten(35, 400, 200, 30, 7, "Mittlere trainings Einheit", cData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);

	bProzessAktiv = false;	// Auf False setzen damit nicht der andere Text ausgegeben wird von aktAusbildung
	cData->getAnimationen().startBenarichtigung(true, "Das Training ist beendet, die Einheit ist jetzt wieder Einsatzbereit");
}

void Traningszentrum::AuswahlZuOrdnen(std::string Name)
{
	sName = Name;
	StartProzess();
}

void Traningszentrum::TrainingLang()
{
	iZeitFaktor = 3;
}

void Traningszentrum::TrainingMittel()
{
	iZeitFaktor = 2;
}

void Traningszentrum::TrainingKurz()
{
	iZeitFaktor = 1;
}

void Traningszentrum::aktstd()
{
}

void Traningszentrum::UpgradeEffizens()
{
}
