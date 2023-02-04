#include "Auswahl.h"

Auswahl::Auswahl(Data* data)
{
	myData = data;

	vKacheln.clear();

	cButtenLinks = new Butten(5, 300, 35, 35, 1, "<", myData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
	cButtenRechts = new Butten(950, 300, 35, 35, 2, ">", myData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
	cButtenUP = new Butten(400, 40, 105, 25, 3, "Aufsteigen", myData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
	cButtenDown = new Butten(550, 40, 105, 25, 4, "Absteigend", myData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
}

Auswahl::~Auswahl()
{
	vKacheln.clear();
	delete cButtenLinks;
	delete cButtenRechts;
	delete cButtenUP;
	delete cButtenDown;
	}

void Auswahl::AnzeigeVorbereitung()
{
	for(int i = 0; i < 2; i++)
	{
		std::stringstream osText;
		osText << "Name: " << myData->getEinheiten()[vAusgewahlteEinheiten[i]].sName << "\nHP: "<< myData->getEinheiten()[vAusgewahlteEinheiten[i]].HP << "\nMoral: " << myData->getEinheiten()[vAusgewahlteEinheiten[i]].Moral << "\nKampfkraft: " << myData->getEinheiten()[vAusgewahlteEinheiten[i]].Starke;
		
		vKacheln.emplace_back(new Kachel(osText.str(), 100, sf::Color::Black, myData->getFont(), 99, 1, 1, vAusgewahlteEinheiten[i], 230 * i + 20 * i + 50, 70, 230, 2 * 200 + 20, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green));
		
		vKacheln[i]->addButten(i * 20 + i * 230 + 60, 450, 200, 30, vAusgewahlteEinheiten[i], "Einheit Auswahlen", myData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White);
		
		osText.str("");
	}
}

std::optional<int> Auswahl::updateAuswahl(sf::Vector2i MousPos)
{
	for (int i = 0; i < vKacheln.size(); i++)
	{
		if (vKacheln[i]->ishover(MousPos))
		{
			vKacheln[i]->sethoverColor();
			//Butten überprüfen
			unsigned short int temp = vKacheln[i]->checkButtenishover(MousPos);
			if (temp != 99)
				if (vKacheln[i]->checkButtenisPressed(temp, MousPos))
				{
						return vKacheln[i]->getID();
				}
				else {}
			else
				vKacheln[i]->setButtenColorToNormal();
		}
		else
		{
			 vKacheln[i]->setNormalColor();
			 vKacheln[i]->setScale(1);
		}
	}
	{
		if (cButtenDown->isHover(MousPos))
		{
			if (cButtenDown->isPressed(MousPos))
			{
				cButtenDown->setPressColor();
				down();
			}
			else
				cButtenDown->setHoverColor();
		}
		else
			cButtenDown->setNormalColor();

		 if (cButtenRechts->isHover(MousPos))
		 {
			 if (cButtenRechts->isPressed(MousPos))
			 {
				 cButtenRechts->setPressColor();
			 }
			 else
				 cButtenRechts->setHoverColor();
		 }
		 else
			 cButtenRechts->setNormalColor();

		 if (cButtenLinks->isHover(MousPos))
		 {
			 if (cButtenLinks->isPressed(MousPos))
			 {
				 cButtenLinks->setPressColor();
			 }
			 else
				 cButtenLinks->setHoverColor();
		 }
		 else
			 cButtenLinks->setNormalColor();

		 if (cButtenUP->isHover(MousPos))
		 {
			 if (cButtenUP->isPressed(MousPos))
			 {
				 cButtenUP->setPressColor();
				 up();
			 }
			 else
				 cButtenUP->setHoverColor();
		 }
		 else
			 cButtenUP->setNormalColor();
	}

	return {};
}

void Auswahl::Mahlen(sf::RenderWindow& window)
{
	for (auto i=0;i<vKacheln.size();i++)
	{
		vKacheln[i]->drawFenster(window);
		vKacheln[i]->drawFenster(window);

		vKacheln[i]->drawText(window);
		vKacheln[i]->drawText(window);
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
		if (myData->getEinheiten()[i].Einsatzbereit)
		{
			vAusgewahlteEinheiten.emplace_back(i);
		}
	}

	AnzeigeVorbereitung();
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

	AnzeigeVorbereitung();
}

void Auswahl::SucheEinsetzbare_UND_GesundeEinheiten()
{
	vAusgewahlteEinheiten.clear();
	for (int i = 0; i < myData->getEinheiten().size(); i++)
	{
		if (myData->getEinheiten()[i].Einsatzbereit && myData->getEinheiten()[i].HP==100)
		{
			vAusgewahlteEinheiten.emplace_back(i);
		}
	}

	AnzeigeVorbereitung();
	
}

void Auswahl::leeren()
{
	for (int i = 0; i < vKacheln.size();)
		vKacheln.erase(vKacheln.begin());

	for (int i = 0; i < vAusgewahlteEinheiten.size();)
		vAusgewahlteEinheiten.erase(vAusgewahlteEinheiten.begin()+i);

}

void Auswahl::up()
{
	//std::sort(vAusgewahlten.begin(), vAusgewahlten.end(), [](const auto& x, const auto& y) { return x.second < y.second; });
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

void Auswahl::down()
{
	//std::sort(vAusgewahlten.begin(), vAusgewahlten.end(), [](const auto& x, const auto& y) { return x.second > y.second; });
}
