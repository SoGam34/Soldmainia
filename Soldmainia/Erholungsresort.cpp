#include "Erholungsresort.h"

Erholungsresort::Erholungsresort() : Gebaeude(24, 4)
{
}

Erholungsresort::Erholungsresort(Data* data) : Gebaeude(data, 24, 4)
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

void Erholungsresort::aktstd()
{
}
