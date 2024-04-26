#include "PreHeader.h"
#include "Auswahl.h"

Auswahl::Auswahl(std::shared_ptr<Data> data)
{
	Daten = data;
	vAusgewahlteEinheiten.clear();
}

Auswahl::~Auswahl()
{
	leeren();
}

void Auswahl::SucheNachEinsetzbarenEinheiten()
{
	vAusgewahlteEinheiten.clear();
	for (int i = 0; i < Daten->getEinheiten().size(); i++)
	{
		if (Daten->getEinheiten()[i].Einsatzbereit)
		{
			vAusgewahlteEinheiten.emplace_back(i);
		}
	}
}

void Auswahl::SucheNachVerletzten()
{
	/*vAusgewahlteEinheiten.clear();
	for (int i = 0; i < myData->getEinheiten().size(); i++)
	{
		if (myData->getEinheiten()[myData->getEinheitsnamen()[i]].HP != 100)
		{
			vAusgewahlteEinheiten.emplace_back(i);
		}
	}

	AnzeigeVorbereitung();
	*/
}

void Auswahl::SucheNachTruppenmoral()
{
	/*vAusgewahlteEinheiten.clear();
	for (int i = 0; i < myData->getEinheiten().size(); i++)
	{
		if (myData->getEinheiten()[myData->getEinheitsnamen()[i]].Moral != 10)
		{
			vAusgewahlteEinheiten.emplace_back(i);
		}
	}

	AnzeigeVorbereitung();
	*/
}

void Auswahl::SucheNachStarke(int min)
{
	/*vAusgewahlteEinheiten.clear();
	for (int i = 0; i < myData->getEinheiten().size(); i++)
	{
		if (myData->getEinheiten()[myData->getEinheitsnamen()[i]].HP >= min)
		{
			vAusgewahlteEinheiten.emplace_back(i);
		}
	}
	*/
}

void Auswahl::SucheEinsetzbare_UND_GesundeEinheiten()
{
	vAusgewahlteEinheiten.clear();
	for (int i = 0; i < Daten->getEinheiten().size(); i++)
	{
		if (Daten->getEinheiten()[i].Einsatzbereit && Daten->getEinheiten()[i].HP==100)
		{
			vAusgewahlteEinheiten.emplace_back(i);
		}
	}
}

void Auswahl::leeren()
{
	for (; 0 < vAusgewahlteEinheiten.size();)
		{
			vAusgewahlteEinheiten.erase(vAusgewahlteEinheiten.begin());
		}
}

void Auswahl::SortiereNachStarke()
{
	/*for (int i = 0; i < vAusgewahlteEinheiten.size(); i++)
	{
		for (int j = 0; j < vAusgewahlteEinheiten.size(); j++)
		{
			if (i > j)
			{
				std::string temp;
				temp = vAusgewahlteEinheiten[j];
				vAusgewahlteEinheiten[j] = vAusgewahlteEinheiten[i];
				vAusgewahlteEinheiten[i] = temp;
			}
		}
	}
	*/
}
