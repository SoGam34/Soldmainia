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
	for (size_t i = 0; i < DatenAuswahl->getMembers().size(); i++)
	{
		// if (DatenAuswahl->getMembers().at(i).getEinsatzbereit() &&
		//     DatenAuswahl->getMembers().at(i).getLeben() == MAX_LEBEN)
		// {
		// 	AusgewahlteEinheiten.push_back(i);
		// }
	}
}
void Auswahl::sucheNachEinsetzbarenEinheiten()
{
	for (size_t i = 0; i < DatenAuswahl->getMembers().size(); i++)
	{
		auto e	   = DatenAuswahl->getMembers().at(i);
		bool ready = false;
		if (e.first.has_value())
		{
			ready = e.first->getReady();
		}
		else
		{
			ready = e.second->getReady();
		}

		if (ready)
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
	for (size_t i = 0; i < DatenAuswahl->getMembers().size(); i++)
	{
		auto e	   = DatenAuswahl->getMembers().at(i);
		bool ready = false;
		if (e.first.has_value())
		{
			ready = e.first->getReady() &&
				e.first->getHealth() == MAX_LEBEN;
		}
		else
		{
			ready = e.second->getReady() &&
				e.second->getHealth() == MAX_LEBEN;
		}

		if (ready)

		{
			AusgewahlteEinheiten.emplace_back(i);
		}
	}

	entferneDopplungen();
}

void Auswahl::sucheNachVerletzten()
{
	for (size_t i = 0; i < DatenAuswahl->getMembers().size(); i++)
	{
		auto e	   = DatenAuswahl->getMembers().at(i);
		bool ready = false;
		if (e.first.has_value())
		{
			ready = e.first->getReady() &&
				e.first->getHealth() < MAX_LEBEN;
		}
		else
		{
			ready = e.second->getReady() &&
				e.second->getHealth() < MAX_LEBEN;
		}

		if (ready)
		{
			AusgewahlteEinheiten.emplace_back(i);
		}
	}

	entferneDopplungen();
}

void Auswahl::sucheNachTruppenmoral()
{
	for (size_t i = 0; i < DatenAuswahl->getMembers().size(); i++)
	{
		auto e	   = DatenAuswahl->getMembers().at(i);
		bool ready = false;
		if (e.first.has_value())
		{
			ready = e.first->getReady() &&
				e.first->getMental() < MAX_MORAL;
		}
		else
		{
			ready = e.second->getReady() &&
				e.second->getMental() < MAX_MORAL;
		}

		if (ready)

		{
			AusgewahlteEinheiten.emplace_back(i);
		}
	}

	entferneDopplungen();
}

void Auswahl::sucheNachStarke(int min)
{
	for (size_t i = 0; i < DatenAuswahl->getMembers().size(); i++)
	{
		auto e	   = DatenAuswahl->getMembers().at(i);
		bool ready = false;
		if (e.first.has_value())
		{
			ready = e.first->getReady() &&
				e.first->getTotalAmountOfDealingDamage() >= min;
		}
		else
		{
			ready =
			    e.second->getReady() &&
			    e.second->getTotalAmountOfDealingDamage() >= min;
		}

		if (ready)
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
			auto I = DatenAuswahl->getMembers().at(i);
			auto J = DatenAuswahl->getMembers().at(j);

			int starkeJ =
			    (J.first.has_value()
				 ? J.first->getTotalAmountOfDealingDamage()
				 : J.second->getTotalAmountOfDealingDamage());
			int starkeI =
			    (I.first.has_value()
				 ? I.first->getTotalAmountOfDealingDamage()
				 : I.second->getTotalAmountOfDealingDamage());

			return starkeI < starkeJ;
		};

		std::sort(AusgewahlteEinheiten.begin(),
			  AusgewahlteEinheiten.end(), comp);
	}

	if (!aufsteigend)
	{
		auto comp = [this](int i, int j)
		{
			auto I = DatenAuswahl->getMembers().at(i);
			auto J = DatenAuswahl->getMembers().at(j);

			int starkeJ =
			    (J.first.has_value()
				 ? J.first->getTotalAmountOfDealingDamage()
				 : J.second->getTotalAmountOfDealingDamage());
			int starkeI =
			    (I.first.has_value()
				 ? I.first->getTotalAmountOfDealingDamage()
				 : I.second->getTotalAmountOfDealingDamage());

			return starkeI > starkeJ;
		};

		std::sort(AusgewahlteEinheiten.begin(),
			  AusgewahlteEinheiten.end(), comp);
	}
}

void Auswahl::sortiereNachVerletzten(bool aufsteigend)
{
	if (aufsteigend)
	{
		auto comp = [this](int i, int j)
		{
			auto I = DatenAuswahl->getMembers().at(i);
			auto J = DatenAuswahl->getMembers().at(j);

			int starkeJ =
			    (J.first.has_value() ? J.first->getHealth()
						 : J.second->getHealth());
			int starkeI =
			    (I.first.has_value() ? I.first->getHealth()
						 : I.second->getHealth());

			return starkeI < starkeJ;
		};

		std::sort(AusgewahlteEinheiten.begin(),
			  AusgewahlteEinheiten.end(), comp);
	}

	if (!aufsteigend)
	{
		auto comp = [this](int i, int j)
		{
			auto I = DatenAuswahl->getMembers().at(i);
			auto J = DatenAuswahl->getMembers().at(j);

			int starkeJ =
			    (J.first.has_value() ? J.first->getHealth()
						 : J.second->getHealth());
			int starkeI =
			    (I.first.has_value() ? I.first->getHealth()
						 : I.second->getHealth());

			return starkeI > starkeJ;
		};

		std::sort(AusgewahlteEinheiten.begin(),
			  AusgewahlteEinheiten.end(), comp);
	}
}

void Auswahl::sortiereNachTruppenmoral(bool aufsteigend)
{

	if (aufsteigend)
	{
		auto comp = [this](int i, int j)
		{
			auto I = DatenAuswahl->getMembers().at(i);
			auto J = DatenAuswahl->getMembers().at(j);

			int starkeJ =
			    (J.first.has_value() ? J.first->getMental()
						 : J.second->getMental());
			int starkeI =
			    (I.first.has_value() ? I.first->getMental()
						 : I.second->getMental());

			return starkeI < starkeJ;
		};

		std::sort(AusgewahlteEinheiten.begin(),
			  AusgewahlteEinheiten.end(), comp);
	}

	if (!aufsteigend)
	{
		auto comp = [this](int i, int j)
		{
			auto I = DatenAuswahl->getMembers().at(i);
			auto J = DatenAuswahl->getMembers().at(j);

			int starkeJ =
			    (J.first.has_value() ? J.first->getMental()
						 : J.second->getMental());
			int starkeI =
			    (I.first.has_value() ? I.first->getHealth()
						 : I.second->getMental());

			return starkeI > starkeJ;
		};

		std::sort(AusgewahlteEinheiten.begin(),
			  AusgewahlteEinheiten.end(), comp);
	}
}
