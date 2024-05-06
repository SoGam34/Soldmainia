#pragma once
#include "Gebaeude.h"
#include "../Data/Data.h"
#include "../Timer.h"

#include <memory>
#include <sstream>

class Zentrale
{
public:
	Zentrale() = delete;
	Zentrale(std::shared_ptr<Data> data);
	~Zentrale();

private:

};

