#include "Erholungsresort.h"

Erholungsresort::Erholungsresort(Data* data) : Gebaeude(data, 24,100,1), Auswahl(data)
{
}

Erholungsresort::~Erholungsresort()
{
}

std::stringstream Erholungsresort::ProzessText()
{
	return std::stringstream();
}

int Erholungsresort::ProzessKosten()
{
	return 0;
}

void Erholungsresort::EndeProzess()
{
}

void Erholungsresort::AuswahlZuOrdnen(std::string Name)
{
	std::cout << Name << "wurde dem trainigszentrum zugeordnet\n";
}

void Erholungsresort::aktstd()
{
	
}

void Erholungsresort::UpgradeEffizens()
{
	//if (cData->getiKontostand() > fUpgradeKosten[1] && iRangmin < 6)								// überprüfen ob die Ausbildung bezahlt werden kann
	//{
	//	iRangmin++;																							// Durchfüren der Verbesserung 
	//	fUpgradeKosten[1] *= 1.6;								// Speichern der neuen Verbesserungskosten
	//	std::stringstream ss;
	//	ss << -fUpgradeKosten[1];
	//	eRang = static_cast<Rang>(rand() % 2 + iRangmin);
	//	iZeitFaktor = eRang;

	//	cData->setiKontostand(cData->getiKontostand() - fUpgradeKosten[1]);					// Abziehn der Verbesserungskosten
	//	cData->getAnimationen().startBenarichtigung(false, ss.str());
	//	cData->getAnimationen().startUpgradeAnimation(3);
	//	if (iRangmin == 6)
	//	{
	//		// Ausgabe des neuen Textes
	//		ss << "Die Maximale Stufe\nwürde erreicht.\nSie können diesen\nPrarameter nicht mehr\noprimieren";
	//		cData->getKacheln(14).neuesBild(ss.str(), 350, 1, 535, 95);
	//	}

	//	else
	//	{
	//		// Ausgabe des neuen Textes
	//		ss << "Das Scoutbüro\nfindet Einzelkampfer die\neinen höheren Rang\nund Potenzial habne\nKosten: " << fUpgradeKosten[1];
	//		cData->getKacheln(14).changeText(ss.str(), 320);
	//	}
	//}
}
