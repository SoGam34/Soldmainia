#include "Auswahl.h"

Auswahl::Auswahl()
{
	myData = nullptr;

	vAusgewahlteEinheiten.clear();
	vKacheln.clear();

	vKacheln.reserve(5);
	vAusgewahlten.reserve(5);
}

Auswahl::Auswahl(Data* data)
{
	myData = data;

	vAusgewahlteEinheiten.clear();
	vKacheln.clear();

	vKacheln.reserve(5);
	vAusgewahlten.reserve(5);

	cButtenLinks = new Butten(5, 300, 10, 5, 1, "<", myData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
	cButtenRechts = new Butten(550, 300, 10, 5, 2, ">", myData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
	cButtenUP = new Butten(240, 60, 10, 5, 3, "Aufsteigen", myData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
	cButtenDown = new Butten(260, 60, 10, 5, 4, "Absteigend", myData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
}

Auswahl::~Auswahl()
{
	for (int i = 0; i < vKacheln.size();)
	{
		delete vKacheln[i];
		vKacheln.erase(vKacheln.begin()+i);
	}

	delete cButtenLinks;
	delete cButtenRechts;
	delete cButtenUP;
	delete cButtenDown;
}

void Auswahl::AnzeigeVorbereitung()
{
	for (int i = 0; i < vAusgewahlteEinheiten.size(); i++)
	{
		std::stringstream osText;
		osText << "Name: " << vAusgewahlteEinheiten[i] << "\nHP: "<< myData->getEinheiten()[vAusgewahlteEinheiten[i]].HP << "\nMoral: " << myData->getEinheiten()[vAusgewahlteEinheiten[i]].Moral << "\nKampfkraft: " << myData->getEinheiten()[vAusgewahlteEinheiten[i]].Starke;
		vKacheln.push_back(new Kachel(osText.str(), 200, sf::Color::Black, myData->getFont(), 99, 1, 1, i+4, 200*i+20*i+15, 70, 230, 2 * 200 + 20, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green));
		vKacheln[i]->addButten(i * 20 + i * 230 + 35, 450, 200, 30, i+4, "Einheit Auswahlen", myData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
		osText.str("");
	}

}

std::optional<std::string> Auswahl::updateAuswahl(sf::Vector2i MousPos)
{
	for (int i = 0; i < vKacheln.size(); i++)
	{
		unsigned short int temp = vKacheln[i]->checkButtenishover(MousPos);
		if (temp != 99)
		{
			if (vKacheln[i]->checkButtenisPressed(temp, MousPos))
			{
				switch (temp)
				{
				case 1: { }break;
				case 2: { }break;
				case 3: {up(); }break;
				case 4: {down(); }break;
				default:
				{
					return vAusgewahlteEinheiten[temp - 4];
				}break;
				}

				break;
			}
		}
	}

	return {};
}

void Auswahl::Mahlen(sf::RenderWindow& window)
{
	for (auto e : vKacheln)
	{
		e->drawFenster(window);
		e->drawFenster(window);
	}

	cButtenDown->drawFenster(window);
	cButtenDown->drawText(window);

	cButtenUP->drawFenster(window);
	cButtenUP->drawText(window);

	cButtenLinks->drawFenster(window);
	cButtenLinks->drawText(window);

	cButtenRechts->drawFenster(window);
	cButtenRechts->drawText(window);
}

void Auswahl::SucheNachEinsetzbarenEinheiten()
{
	vAusgewahlteEinheiten.clear();
	for (int i = 0; i < myData->getEinheiten().size(); i++)
	{
		if (myData->getEinheiten()[myData->getEinheitsnamen()[i]].Einsatzbereit)
		{
			std::string temp = myData->getEinheitsnamen()[i];
			vAusgewahlteEinheiten.emplace_back(temp);
		}
	}

	AnzeigeVorbereitung();
}

void Auswahl::SucheNachVerletzten()
{
	vAusgewahlteEinheiten.clear();
	for (int i = 0; i < myData->getEinheiten().size(); i++)
	{
		if (myData->getEinheiten()[myData->getEinheitsnamen()[i]].HP != 100)
		{
			std::string temp = myData->getEinheitsnamen()[i];
			vAusgewahlteEinheiten.emplace_back(temp);
		}
	}

	AnzeigeVorbereitung();
}

void Auswahl::SucheNachTruppenmoral()
{
	vAusgewahlteEinheiten.clear();
	for (int i = 0; i < myData->getEinheiten().size(); i++)
	{
		if (myData->getEinheiten()[myData->getEinheitsnamen()[i]].Moral != 10)
		{
			std::string temp = myData->getEinheitsnamen()[i];
			vAusgewahlteEinheiten.emplace_back(temp);
		}
	}

	AnzeigeVorbereitung();
}

void Auswahl::SucheNachStarke(int min)
{
	vAusgewahlteEinheiten.clear();
	for (int i = 0; i < myData->getEinheiten().size(); i++)
	{
		if (myData->getEinheiten()[myData->getEinheitsnamen()[i]].HP >= min)
		{
			std::string temp = myData->getEinheitsnamen()[i];
			vAusgewahlteEinheiten.emplace_back(temp);
		}
	}

	AnzeigeVorbereitung();
}

void Auswahl::SucheEinsetzbare_UND_GesundeEinheiten()
{
	vAusgewahlteEinheiten.clear();
	for (int i = 0; i < myData->getEinheiten().size(); i++)
	{
		if (myData->getEinheiten()[myData->getEinheitsnamen()[i]].Einsatzbereit && myData->getEinheiten()[myData->getEinheitsnamen()[i]].HP==100)
		{
			std::string temp = myData->getEinheitsnamen()[i];
			vAusgewahlteEinheiten.emplace_back(temp);
		}
	}

	AnzeigeVorbereitung();
}

void Auswahl::up()
{
	std::sort(vAusgewahlten.begin(), vAusgewahlten.end(),
		[](const auto& x, const auto& y) { return x.second < y.second; });
}

void Auswahl::SortiereNachStarke()
{
	for (int i = 0; i < vAusgewahlteEinheiten.size(); i++)
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
}

void Auswahl::down()
{
	std::sort(vAusgewahlten.begin(), vAusgewahlten.end(),
		[](const auto& x, const auto& y) { return x.second > y.second; });
}

std::string Auswahl::getEinheitsname(int ButtenID)
{
	return vAusgewahlteEinheiten[ButtenID-4];
}
