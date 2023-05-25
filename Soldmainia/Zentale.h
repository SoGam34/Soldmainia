#pragma once
#include "Data.h"
#include "Gebaeude.h"

class Zentale
{
public:
	Zentale()=delete;
	Zentale(std::shared_ptr<Data> data, std::mutex& mutex);
	~Zentale();

private:
	std::shared_ptr<Data> cData;

};

