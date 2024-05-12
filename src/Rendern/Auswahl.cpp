#include "Auswahl.h"

Auswahl::Auswahl(std::shared_ptr<Data> data)
{
	DatenAuswahl = data;
	AusgewahlteEinheiten.clear();
}

Auswahl::~Auswahl()
{
	leeren();
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
	for (size_t i = 0; 0 < AusgewahlteEinheiten.size(); i++)
	{
		for (size_t j = 0; j < AusgewahlteEinheiten.size(); j++)
		{
			if (AusgewahlteEinheiten[i] == AusgewahlteEinheiten[j] && i != j)
			{
				//AusgewahlteEinheiten[j].pop_back();  TODO: Remove the Element on position j
			}
		}
	}
}

void Auswahl::sucheNachUnverletztenEinheiten()
{
	for (size_t i = 0; i < DatenAuswahl->getEinheiten().size(); i++)
	{
		if (DatenAuswahl->getEinheiten()[i].getEinsatzbereit()
				&& DatenAuswahl->getEinheiten()[i].getLeben() == MAX_LEBEN)
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
		if (DatenAuswahl->getEinheiten()[i].getEinsatzbereit()
				&& DatenAuswahl->getEinheiten()[i].getLeben() < MAX_LEBEN)
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
		if (DatenAuswahl->getEinheiten()[i].getEinsatzbereit()
				&& DatenAuswahl->getEinheiten()[i].getMoral() < MAX_MORAL)
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
		if (DatenAuswahl->getEinheiten()[i].getEinsatzbereit()
				&& DatenAuswahl->getEinheiten()[i].getStarke() >= min)
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
		for (size_t i = 0; i < AusgewahlteEinheiten.size(); i++)
		{
			for (size_t j = 0; j < AusgewahlteEinheiten.size(); j++)
			{
				if (DatenAuswahl->getEinheiten()[AusgewahlteEinheiten[i]].getStarke()
						> DatenAuswahl->getEinheiten()[AusgewahlteEinheiten[j]].getStarke())
				{
					size_t temp;
					temp = AusgewahlteEinheiten[j];
					AusgewahlteEinheiten[j] = AusgewahlteEinheiten[i];
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
				if (DatenAuswahl->getEinheiten()[AusgewahlteEinheiten[i]].getStarke()
						< DatenAuswahl->getEinheiten()[AusgewahlteEinheiten[j]].getStarke())
				{
					size_t temp;
					temp = AusgewahlteEinheiten[j];
					AusgewahlteEinheiten[j] = AusgewahlteEinheiten[i];
					AusgewahlteEinheiten[i] = temp;
				}
			}
		}
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
				if (DatenAuswahl->getEinheiten()[AusgewahlteEinheiten[i]].getLeben()
						> DatenAuswahl->getEinheiten()[AusgewahlteEinheiten[j]].getLeben())
				{
					size_t temp;
					temp = AusgewahlteEinheiten[j];
					AusgewahlteEinheiten[j] = AusgewahlteEinheiten[i];
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
				if (DatenAuswahl->getEinheiten()[AusgewahlteEinheiten[i]].getLeben()
						< DatenAuswahl->getEinheiten()[AusgewahlteEinheiten[j]].getLeben())
				{
					size_t temp;
					temp = AusgewahlteEinheiten[j];
					AusgewahlteEinheiten[j] = AusgewahlteEinheiten[i];
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
				if (DatenAuswahl->getEinheiten()[AusgewahlteEinheiten[i]].getMoral()
						> DatenAuswahl->getEinheiten()[AusgewahlteEinheiten[j]].getMoral())
				{
					size_t temp;
					temp = AusgewahlteEinheiten[j];
					AusgewahlteEinheiten[j] = AusgewahlteEinheiten[i];
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
				if (DatenAuswahl->getEinheiten()[AusgewahlteEinheiten[i]].getMoral()
						< DatenAuswahl->getEinheiten()[AusgewahlteEinheiten[j]].getMoral())
				{
					size_t temp;
					temp = AusgewahlteEinheiten[j];
					AusgewahlteEinheiten[j] = AusgewahlteEinheiten[i];
					AusgewahlteEinheiten[i] = temp;
				}
			}
		}
	}
}

