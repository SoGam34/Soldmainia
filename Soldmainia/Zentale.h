#pragma once
#include "Data.h"

class Zentale
{
public:
	Zentale()=delete;
	Zentale(Data* data, std::mutex& mutex);
	~Zentale();

private:
	Data* cData;

};

