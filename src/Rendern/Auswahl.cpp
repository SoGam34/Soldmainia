#include "Auswahl.h"
#include <algorithm>
#include <cstddef>
#include <functional>
#include <utility>

Auswahl::Auswahl(std::shared_ptr<Data>& data) : DatenAuswahl(data)
{

	AusgewahlteEinheiten.clear();
}

Auswahl::~Auswahl()
{
	leeren();
}
void Auswahl::sucheNachUnverletztenEinsetzbarenEinheiten()
{
	for (size_t i = 0; i < DatenAuswahl->getEinheiten().size(); i++)
	{
		if (DatenAuswahl->getEinheiten().at(i).getEinsatzbereit() &&
		    DatenAuswahl->getEinheiten().at(i).getLeben() == MAX_LEBEN)
		{
			AusgewahlteEinheiten.push_back(i);
		}
	}
}
void Auswahl::sucheNachEinsetzbarenEinheiten()
{
	for (size_t i = 0; i < DatenAuswahl->getEinheiten().size(); i++)
	{
		if (DatenAuswahl->getEinheiten()[i].getEinsatzbereit())
		{
			AusgewahlteEinheiten.emplace_back(i);
		}
	}

	entferneDopplungen();
}

void Auswahl::entferneDopplungen()
{
	for (auto i = AusgewahlteEinheiten.begin();
	     i != AusgewahlteEinheiten.end(); i++)
	{
		for (auto j = AusgewahlteEinheiten.begin();
		     j != AusgewahlteEinheiten.end(); j++)
		{
			if (*i == *j && i != j)
			{
				AusgewahlteEinheiten.erase(j);
			}
		}
	}
}

void Auswahl::sucheNachUnverletztenEinheiten()
{
	for (size_t i = 0; i < DatenAuswahl->getEinheiten().size(); i++)
	{
		if (DatenAuswahl->getEinheiten()[i].getEinsatzbereit() &&
		    DatenAuswahl->getEinheiten()[i].getLeben() == MAX_LEBEN)
		{
			AusgewahlteEinheiten.emplace_back(i);
		}
	}

	entferneDopplungen();
}

void Auswahl::sucheNachVerletzten()
{
	for (size_t i = 0; i < DatenAuswahl->getEinheiten().size(); i++)
	{
		if (DatenAuswahl->getEinheiten()[i].getEinsatzbereit() &&
		    DatenAuswahl->getEinheiten()[i].getLeben() < MAX_LEBEN)
		{
			AusgewahlteEinheiten.emplace_back(i);
		}
	}

	entferneDopplungen();
}

void Auswahl::sucheNachTruppenmoral()
{
	for (size_t i = 0; i < DatenAuswahl->getEinheiten().size(); i++)
	{
		if (DatenAuswahl->getEinheiten()[i].getEinsatzbereit() &&
		    DatenAuswahl->getEinheiten()[i].getMoral() < MAX_MORAL)
		{
			AusgewahlteEinheiten.emplace_back(i);
		}
	}

	entferneDopplungen();
}

void Auswahl::sucheNachStarke(int min)
{
	for (size_t i = 0; i < DatenAuswahl->getEinheiten().size(); i++)
	{
		if (DatenAuswahl->getEinheiten()[i].getEinsatzbereit() &&
		    DatenAuswahl->getEinheiten()[i].getStarke() >= min)
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

void Auswahl::sortiereNachStarke(bool aufsteigend)
{
	if (aufsteigend)
	{
		auto comp = [this](int i, int j)
		{
			return DatenAuswahl->getEinheiten()[i].getStarke() <
			       DatenAuswahl->getEinheiten()[j].getStarke();
		};

		std::sort(AusgewahlteEinheiten.begin(),
			  AusgewahlteEinheiten.end(), comp);
	}

	if (!aufsteigend)
	{
		auto comp = [this](int i, int j)
		{
			return DatenAuswahl->getEinheiten()[i].getStarke() >
			       DatenAuswahl->getEinheiten()[j].getStarke();
		};

		std::sort(AusgewahlteEinheiten.begin(),
			  AusgewahlteEinheiten.end(), comp);
	}
}

void Auswahl::sortiereNachVerletzten(bool aufsteigend)
{
	if (aufsteigend)
	{
		for (size_t i = 0; i < AusgewahlteEinheiten.size(); i++)
		{
			for (size_t j = 0; j < AusgewahlteEinheiten.size(); j++)
			{
				if (DatenAuswahl
					->getEinheiten()
					    [AusgewahlteEinheiten[i]]
					.getLeben() >
				    DatenAuswahl
					->getEinheiten()
					    [AusgewahlteEinheiten[j]]
					.getLeben())
				{
					size_t temp;
					temp = AusgewahlteEinheiten[j];
					AusgewahlteEinheiten[j] =
					    AusgewahlteEinheiten[i];
					AusgewahlteEinheiten[i] = temp;
				}
			}
		}
	}

	else if (!aufsteigend)
	{
		for (size_t i = 0; i < AusgewahlteEinheiten.size(); i++)
		{
			for (size_t j = 0; j < AusgewahlteEinheiten.size(); j++)
			{
				if (DatenAuswahl
					->getEinheiten()
					    [AusgewahlteEinheiten[i]]
					.getLeben() <
				    DatenAuswahl
					->getEinheiten()
					    [AusgewahlteEinheiten[j]]
					.getLeben())
				{
					size_t temp;
					temp = AusgewahlteEinheiten[j];
					AusgewahlteEinheiten[j] =
					    AusgewahlteEinheiten[i];
					AusgewahlteEinheiten[i] = temp;
				}
			}
		}
	}
}

void Auswahl::sortiereNachTruppenmoral(bool aufsteigend)
{
	if (aufsteigend)
	{
		for (size_t i = 0; i < AusgewahlteEinheiten.size(); i++)
		{
			for (size_t j = 0; j < AusgewahlteEinheiten.size(); j++)
			{
				if (DatenAuswahl
					->getEinheiten()
					    [AusgewahlteEinheiten[i]]
					.getMoral() >
				    DatenAuswahl
					->getEinheiten()
					    [AusgewahlteEinheiten[j]]
					.getMoral())
				{
					size_t temp;
					temp = AusgewahlteEinheiten[j];
					AusgewahlteEinheiten[j] =
					    AusgewahlteEinheiten[i];
					AusgewahlteEinheiten[i] = temp;
				}
			}
		}
	}

	else if (!aufsteigend)
	{
		for (size_t i = 0; i < AusgewahlteEinheiten.size(); i++)
		{
			for (size_t j = 0; j < AusgewahlteEinheiten.size(); j++)
			{
				if (DatenAuswahl
					->getEinheiten()
					    [AusgewahlteEinheiten[i]]
					.getMoral() <
				    DatenAuswahl
					->getEinheiten()
					    [AusgewahlteEinheiten[j]]
					.getMoral())
				{
					size_t temp;
					temp = AusgewahlteEinheiten[j];
					AusgewahlteEinheiten[j] =
					    AusgewahlteEinheiten[i];
					AusgewahlteEinheiten[i] = temp;
				}
			}
		}
	}
}
