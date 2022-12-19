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

	sfBenarichtigungsText.setCharacterSize(17);
	sfBenarichtigungsText.setPosition(20, 40);
}

Animationen::Animationen(sf::Font font)
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

	sfBenarichtigungsText.setCharacterSize(17);
	sfBenarichtigungsText.setPosition(20, 40);
	sfBenarichtigungsText.setFont(font);
}

Animationen::~Animationen()
{

}

void Animationen::Aktualisieren()
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
			r += 6;
			b -= 6;
			g -= 2;
		}

		else if (!bBenarichtigungsArt && sBenarichtigung <= 30)
		{
			r -= 6;
			b += 6;
			g += 2;
		}

		else if (bBenarichtigungsArt&&sBenarichtigung>30)
		{
			r -= 2;
			b -= 6;
			g += 6;
		}

		else
		{
			r += 2;
			b += 6;
			g -= 6;
		}
			
		
	}

	if (sBenarichtigung == 0)
	{
		r = g = 60;
		b = 180;
	}
}

void Animationen::draw(sf::RenderTarget* window)
{
	if (sUpgradeAnimation>0)
	{
		for(auto i:Pfeile)
			window->draw(i);
	}

	if (sBenarichtigung > 0)
	{
		window->draw(sfBenarichtigungsText);
	}
}

void Animationen::startUpgradeAnimation(int Spalte, int breite, int hohe)
{
	sUpgradeAnimation = 100;
	int tempx;
	int tempy;
	for (int i = 0; i < Pfeile.size(); i++)
	{
		tempx = rand() % ((breite/2)-40) + 30;
		tempy = rand() % hohe + 190;

		if (breite < 250)
			tempx += (Spalte > 3) ? 20 : 0;

		else
			tempx += (Spalte > 3) ? breite+50 : ((Spalte > 2) ? 150 : 60);
		Pfeile[i].setPosition(((Spalte - 1) * 230) +(Spalte*20) + tempx, tempy);
	}
}

void Animationen::startBenarichtigung(bool gut, std::string Text)
{
	r = g = 60;
	b = 180;
	sBenarichtigung = 60;
	bBenarichtigungsArt = gut;

	sfBenarichtigungsText.setString(Text);
}

void Animationen::clearWindow(sf::RenderTarget* window)
{
	window->clear(sf::Color(r, g, b, 200));
}

void Animationen::setFont(sf::Font* font)
{
	sfBenarichtigungsText.setFont(*font);
}
