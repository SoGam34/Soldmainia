#pragma once
#include "Gebaeude.h"
#include "Auswahl.h"

class Traningszentrum : public Gebaeude, public Auswahl
{
public:
	Traningszentrum(Data* data);
	~Traningszentrum();

	//Ausbildungs F.
	std::stringstream ProzessText();
	int ProzessKosten();
	void EndeProzess();
	void AuswahlZuOrdnen(std::string Name);

	void TrainingLang();
	void TrainingMittel();
	void TrainingKurz();

	//Sonstige Funktonen
	void aktstd();
	void UpgradeEffizens();

private:
	std::string sName;
};

