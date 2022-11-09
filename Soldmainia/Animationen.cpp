#include "Animationen.h"

Animationen::Animationen()
{
	UpgradePfeil.loadFromFile("Texturen/Pfeil.png");
	sf::Sprite temp;
	temp.setTexture(UpgradePfeil);
	Pfeile.push_back(temp);
	Pfeile.push_back(temp);
	Pfeile.push_back(temp);

	sBenarichtigung = sUpgradeAnimation = 0;

	r = g = 60;
	b = 180;
}

Animationen::~Animationen()
{

}

void Animationen::Aktualisieren(sf::RenderTarget* window)
{
	if (sUpgradeAnimation > 0)
	{
		sUpgradeAnimation--;
		for (auto &i : Pfeile)
		{
			if (i.getPosition().y > 100)
				i.move(0, -4);

			else 
				i.setPosition(i.getPosition().x, -80);
		}
	}

	if (sBenarichtigung > 0)
	{
		sBenarichtigung--;
		if (!bBenarichtigungsArt&&sBenarichtigung>30)
		{
			r += 5;
			b -= 5;
			g -= 1;
		}

		else if (!bBenarichtigungsArt && sBenarichtigung <= 30)
		{
			r -= 5;
			b += 5;
			g += 1;
		}

		else if (bBenarichtigungsArt&&sBenarichtigung>30)
		{
			r -= 1;
			b -= 5;
			g += 5;
		}

		else
		{
			r += 1;
			b += 5;
			g -= 5;
		}
			
		
	}

	if (sBenarichtigung == 0)
	{
		r = g = 60;
		b = 180;
	}

	window->clear(sf::Color(r, g, b, 200));

}

void Animationen::draw(sf::RenderWindow* window)
{
	if (sUpgradeAnimation>0)
	{
		for(auto i:Pfeile)
			window->draw(i);
	}
}

void Animationen::startUpgradeAnimation(int Spalte)
{
	sUpgradeAnimation = 100;
	int tempx;
	int tempy;
	for (int i = 0; i < Pfeile.size(); i++)
	{
		tempx = rand() % 130+30;
		tempy = rand() % 150 + 160;
		Pfeile[i].setPosition(((Spalte - 1) * 230) + tempx, tempy);
	}
}

void Animationen::startBenarichtigung(bool gut)
{
	r = g = 60;
	b = 180;
	sBenarichtigung = 60;
	bBenarichtigungsArt = gut;
}
