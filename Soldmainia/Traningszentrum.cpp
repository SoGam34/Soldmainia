#include "Traningszentrum.h"

Traningszentrum::Traningszentrum() : Gebaeude(16, 2), Auswahl()
{
}

Traningszentrum::Traningszentrum(Data*data) : Gebaeude(data, 16, 2), Auswahl(data)
{
}

Traningszentrum::~Traningszentrum()
{
}

std::stringstream Traningszentrum::ProzessText()
{
	return std::stringstream();
}

int Traningszentrum::ProzessKosten()
{
	return 0;
}

void Traningszentrum::EndeProzess()
{
}

void Traningszentrum::AuswahlZuOrdnen(std::string Name)
{
	std::cout << Name << "wurde dem trainigszentrum zugeordnet\n";
}

void Traningszentrum::aktstd()
{
}

void Traningszentrum::UpgradeEffizens()
{
}
