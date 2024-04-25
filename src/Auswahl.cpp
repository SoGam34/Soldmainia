#include "PreHeader.h"
#include "Auswahl.h"

Auswahl::Auswahl(std::shared_ptr<Data> data, std::mutex& mutex)
{
	myData = data;

	vKacheln.clear();
	vAusgewahlteEinheiten.clear();
	{
		std::lock_guard<std::mutex> lock(mutex);
		cButtenLinks = new Button(5, 300, 35, 35, 1, "<", *myData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White, 100, 100);
		cButtenRechts = new Button(950, 300, 35, 35, 2, ">", *myData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White, 100, 100);
		cButtenUP = new Button(400, 40, 105, 25, 3, "Aufsteigen", *myData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White, 100, 100);
		cButtenDown = new Button(550, 40, 105, 25, 4, "Absteigend", *myData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White, 100, 100);
	}
}

Auswahl::~Auswahl()
{
	leeren();
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
		
		vKacheln.emplace_back(new Kachel(osText.str(), 100, sf::Color::Black, *myData->getFont(), 99, 1, 1, vAusgewahlteEinheiten[i], 230 * i + 20 * i + 50, 70, 230, 2 * 200 + 20, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green));
		
		vKacheln[i]->ButtonHinzufuegen(i * 20 + i * 230 + 60, 450, 200, 30, vAusgewahlteEinheiten[i], "Einheit Auswahlen", *myData->getFont(), sf::Color::Black, sf::Color(100, 100, 100), sf::Color(50, 50, 50), sf::Color::White, myData->getKacheln(i).getGroese().x, myData->getKacheln(i).getGroese().y);
		
		osText.str("");
	}
}

std::optional<int> Auswahl::updateAuswahl(sf::Vector2i MousPos)
{
	for (int i = 0; i < vKacheln.size(); i++)
	{
		if (vKacheln[i]->MausSchwebtDrueber(MousPos))
		{
			vKacheln[i]->setKachel_Schwebefarbe();
			//Butten �berpr�fen
			std::optional<unsigned int> temp = vKacheln[i]->ueberprueftAlleButtonObMausSchwebtDrueber(MousPos);
			if (temp.has_value())
				if (vKacheln[i]->ueberprueftButtonObGedruektWird(temp.value()))
				{
						return vKacheln[i]->getID();
				}
				else {}
			else
				vKacheln[i]->setAlleButtenAufHintergrundfarbe();
		}
		else
		{
			 vKacheln[i]->setKachel_Hintergrundfarbe();
			 vKacheln[i]->setTextureGroessenSkalierungsFaktor(1);
		}
	}
	{
		if (cButtenDown->MausSchwebtDrueber(MousPos))
		{
			if (cButtenDown->wirdGedrueckt())
			{
				cButtenDown->setButton_Gedruecktfarbe();
				down();
			}
			else
				cButtenDown->setButton_Schwebefarbe();
		}
		else
			cButtenDown->setButton_Hintergrundfarbe();

		 if (cButtenRechts->MausSchwebtDrueber(MousPos))
		 {
			 if (cButtenRechts->wirdGedrueckt())
			 {
				 cButtenRechts->setButton_Gedruecktfarbe();
			 }
			 else
				 cButtenRechts->setButton_Schwebefarbe();
		 }
		 else
			 cButtenRechts->setButton_Hintergrundfarbe();

		 if (cButtenLinks->MausSchwebtDrueber(MousPos))
		 {
			 if (cButtenLinks->wirdGedrueckt())
			 {
				 cButtenLinks->setButton_Gedruecktfarbe();
			 }
			 else
				 cButtenLinks->setButton_Schwebefarbe();
		 }
		 else
			 cButtenLinks->setButton_Hintergrundfarbe();

		 if (cButtenUP->MausSchwebtDrueber(MousPos))
		 {
			 if (cButtenUP->wirdGedrueckt())
			 {
				 cButtenUP->setButton_Gedruecktfarbe();
				 up();
			 }
			 else
				 cButtenUP->setButton_Schwebefarbe();
		 }
		 else
			 cButtenUP->setButton_Hintergrundfarbe();
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
	for (; 0 < vKacheln.size();)
		{
			vKacheln.erase(vKacheln.begin());
		}

	for (; 0 < vAusgewahlteEinheiten.size();)
		{
			vAusgewahlteEinheiten.erase(vAusgewahlteEinheiten.begin());
		}
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
