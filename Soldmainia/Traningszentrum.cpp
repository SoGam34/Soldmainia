#include "Traningszentrum.h"

Traningszentrum::Traningszentrum() : Gebaeude(16, 2)
{
}

Traningszentrum::Traningszentrum(Data*data) : Gebaeude(data, 16, 2)
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

void Traningszentrum::aktstd()
{
}

void Traningszentrum::UpgradeEffizens()
{
}
