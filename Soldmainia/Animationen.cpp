#include "PreHeader.h"
#include "Animationen.h"

Animationen::Animationen()
{

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

	kBenarichtigung = nullptr;

	bKeinBenarichtigung = false;
}

Animationen::~Animationen()
{
	delete kBenarichtigung;
}

void Animationen::Aktualisieren(sf::Vector2i vMauspos)
{
	if (bKeinBenarichtigung)
	{
		if (sBenarichtigung == 0)
		{
			startBenarichtigung(false, "");
		}

		kBenarichtigung->aktualisieren();
		//Kacheln ueberpruefen
		if (kBenarichtigung->MausSchwebtDrueber(vMauspos))
		{
			kBenarichtigung->setKachel_Schwebefarbe();
			//Butten ueberpruefen
			if(kBenarichtigung->ueberprueftAlleButtonObMausSchwebtDrueber(vMauspos)==1)
				if (kBenarichtigung->ueberprueftButtonObGedruektWird(1))
				{
					bKeinBenarichtigung = false;
					sBenarichtigung = 0;
				}
				else{ }
			else
				kBenarichtigung->setAlleButtenAufHintergrundfarbe();
		}
		else
			kBenarichtigung->setKachel_Hintergrundfarbe();
	}
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
	if (bKeinBenarichtigung)
	{
		kBenarichtigung->drawFenster(*window);
		kBenarichtigung->drawText(*window);
	}

	if (sUpgradeAnimation>0)
	{
		for(auto &i:Pfeile)
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

void Animationen::KeinGeld(sf::Vector2f Pos, sf::Font* font)
{
	kBenarichtigung = new Kachel("Sie haben nicht\ngenungend Geld um\ndie gewunschte Aktion\ndurchzufuhren", 100, sf::Color::Black, *font, 99, 1 * 20, 95, 9, (Pos.x / 2) - 200, 70, 400, 300, sf::Color(250,10,10), sf::Color(255, 240, 200), sf::Color::Green);
	kBenarichtigung->ButtonHinzufuegen((Pos.x / 2) - 100, 300, 200, 30, 1, "Bestaetigen", *font, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, kBenarichtigung->getGroese().x, kBenarichtigung->getGroese().y);
	bKeinBenarichtigung = true;
	startBenarichtigung(false, "");
}

void Animationen::KeineBerechtigung(sf::Vector2f Pos, sf::Font* font)
{
	kBenarichtigung = new Kachel("Sie sind nicht\nBerechtigt die Aktion\ndurchzufuehren", 80, sf::Color::Black, *font, 99, 1 * 20, 95, 9, (Pos.x/2)-200, 70, 400, 300, sf::Color::Red, sf::Color(255, 200, 200), sf::Color::Green);
	kBenarichtigung->ButtonHinzufuegen(350, (Pos.y-2) + 50, 200, 30, 1, "Bestaetigen", *font, sf::Color::Black, sf::Color(100, 100, 100), sf::Color(255, 150, 0), sf::Color::White, kBenarichtigung->getGroese().x, kBenarichtigung->getGroese().y);
	startBenarichtigung(false, "");
}

bool Animationen::getKeineBenarichtigung()
{
	return bKeinBenarichtigung;
}

void Animationen::updateKachelPos(int PosX, int PosY, int Breite, int Hohe)
{
	if (kBenarichtigung != nullptr)
		kBenarichtigung->aktualisierenPosition(PosX, PosY, Breite, Hohe);
}
