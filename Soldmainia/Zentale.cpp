#include "Zentale.h"

Zentale::Zentale(std::shared_ptr<Data> data, std::mutex& mutex)
{
	cData = data;
}

Zentale::~Zentale()
{
}
