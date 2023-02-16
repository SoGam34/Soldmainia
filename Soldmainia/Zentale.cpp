#include "Zentale.h"

Zentale::Zentale(Data* data, std::mutex& mutex)
{
	cData = data;
}

Zentale::~Zentale()
{
}
