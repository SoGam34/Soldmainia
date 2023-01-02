#pragma once
#include "Data.h"

class Zentale
{
public:
	Zentale();
	Zentale(Data* data);
	~Zentale();

private:
	Data* cData;

};

