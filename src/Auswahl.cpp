#include "Auswahl.h"

Auswahl::Auswahl(std::shared_ptr<Data> data)
{
	Daten = data;
	AusgewahlteEinheiten.clear();
}

Auswahl::~Auswahl()
{
	leeren();
}

void Auswahl::sucheNachEinsetzbarenEinheiten()
{
	for (size_t i = 0; i < Daten->getEinheiten().size(); i++)
	{
		if (Daten->getEinheiten()[i].getEinsatzbereit())
		{
			AusgewahlteEinheiten.emplace_back(i);
		}
	}

	entferneDopplungen();
}

void Auswahl::entferneDopplungen()
{
	for (std::vector<int>::iterator i = AusgewahlteEinheiten.begin();
			0 < AusgewahlteEinheiten.size(); i++)
	{
		for (std::vector<int>::iterator j = AusgewahlteEinheiten.begin();
				j < AusgewahlteEinheiten.size(); j++)
		{
			if (AusgewahlteEinheiten[i] == AusgewahlteEinheiten[j] && i != j)
			{
				AusgewahlteEinheiten.erase(j);
			}
		}
	}
}

void Auswahl::sucheNachVerletzten()
{
	for (size_t i = 0; i < Daten->getEinheiten().size(); i++)
	{
		if (Daten->getEinheiten()[i].getLeben() < MAX_LEBEN)
		{
			AusgewahlteEinheiten.emplace_back(i);
		}
	}

	entferneDopplungen();
}

void Auswahl::sucheNachTruppenmoral()
{
	for (size_t i = 0; i < Daten->getEinheiten().size(); i++)
	{
		if (Daten->getEinheiten()[i].getMoral() < MAX_MORAL)
		{
			AusgewahlteEinheiten.emplace_back(i);
		}
	}

	entferneDopplungen();
}

void Auswahl::sucheNachStarke(int min)
{
	for (size_t i = 0; i < Daten->getEinheiten().size(); i++)
	{
		if (Daten->getEinheiten()[i].getStarke() >= min)
		{
			AusgewahlteEinheiten.emplace_back(i);
		}
	}

	entferneDopplungen();
}

void Auswahl::leeren()
{
	for (; 0 < AusgewahlteEinheiten.size();)
	{
		AusgewahlteEinheiten.erase(AusgewahlteEinheiten.begin());
	}
}

void Auswahl::sortiereNachStarke()
{
	for (size_t i = 0; i < AusgewahlteEinheiten.size(); i++)
	{
		for (size_t j = 0; j < AusgewahlteEinheiten.size(); j++)
		{
			if (Daten->getEinheiten()[AusgewahlteEinheiten[i]].getStarke()
					> Daten->getEinheiten()[AusgewahlteEinheiten[j]].getStarke())
			{
				size_t temp;
				temp = AusgewahlteEinheiten[j];
				AusgewahlteEinheiten[j] = AusgewahlteEinheiten[i];
				AusgewahlteEinheiten[i] = temp;
			}
		}
	}
}

void Auswahl::sortiereNachVerletzten()
{
	for (size_t i = 0; i < AusgewahlteEinheiten.size(); i++)
	{
		for (size_t j = 0; j < AusgewahlteEinheiten.size(); j++)
		{
			if (Daten->getEinheiten()[AusgewahlteEinheiten[i]].getLeben()
					> Daten->getEinheiten()[AusgewahlteEinheiten[j]].getLeben())
			{
				size_t temp;
				temp = AusgewahlteEinheiten[j];
				AusgewahlteEinheiten[j] = AusgewahlteEinheiten[i];
				AusgewahlteEinheiten[i] = temp;
			}
		}
	}
}

void Auswahl::sortiereNachTruppenmoral()
{
	for (size_t i = 0; i < AusgewahlteEinheiten.size(); i++)
	{
		for (size_t j = 0; j < AusgewahlteEinheiten.size(); j++)
		{
			if (Daten->getEinheiten()[AusgewahlteEinheiten[i]].getMoral()
					> Daten->getEinheiten()[AusgewahlteEinheiten[j]].getMoral())
			{
				size_t temp;
				temp = AusgewahlteEinheiten[j];
				AusgewahlteEinheiten[j] = AusgewahlteEinheiten[i];
				AusgewahlteEinheiten[i] = temp;
			}
		}
	}
}

