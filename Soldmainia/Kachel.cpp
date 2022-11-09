#include "Kachel.h"

//Konstruktoren#include "stdafx.h"
Kachel::Kachel()
{
	bdruken = false;
}

Kachel::Kachel(std::string Text, int PosTextY, sf::Color TextColor, sf::Font* font,
	int IDTexture, int PosTextureX, int PosTextureY, 
	int ID, int PosKachelX, int PosKachelY, float with, float height,
	sf::Color backroundColor, sf::Color hoverColor, sf::Color pressColor)
{
	// Texture
	iIDTexture = IDTexture;
	iPosTextureX = PosTextureX;
	iPosTextureY = PosTextureY;
	//Kachel
	iID = ID;
	kachel.setPosition(PosKachelX, PosKachelY);
	kachel.setSize(sf::Vector2f(with, height));
	tText.setCharacterSize(15);
	sfBackroundColor = backroundColor;
	sfHoverColor = hoverColor;
	sfPressColor = pressColor;
	kachel.setFillColor(sfBackroundColor);
	bdruken = false;
	// Text
	tText.setFont(*font);
	tText.setFillColor(TextColor);
	newText(Text, PosTextY);
	//Butten
	vButten.clear();

	
}

Kachel::~Kachel()
{
	for (int i = 0; i < vButten.size();)
	{
		delete vButten[i];
		vButten.erase(vButten.begin() + i);
	}
	vButten.clear();
}
//Funktionen zum dieseignen und Mahlen der Kachel
 void Kachel::addButten(float x, float y, float with, float heigth, int ID,
							std::string text, sf::Font* font,
							sf::Color backroundColor, sf::Color hoverColor, sf::Color PressColor, sf::Color textColor)
{
	vButten.push_back(new Butten(x, y, with, heigth, ID, text, font, backroundColor, hoverColor, PressColor, textColor));
	}

void Kachel::neuesBild(std::string Text,  int PosTextY,
					 int IDTexture, int PosTextureX, int PosTextureY)
{
	for (int i = 0; i < vButten.size();)
	{
		delete vButten[i];
		vButten.erase(vButten.begin() + i);
	}

	newText(Text, PosTextY);
	// Texture
	iIDTexture = IDTexture;
	iPosTextureX = PosTextureX;
	iPosTextureY = PosTextureY;
}

void Kachel::changeText(std::string Text, int PosTextY)
{
	newText(Text, PosTextY);
}

void Kachel::draw(sf::RenderTarget& target)
{
	target.draw(kachel);
	target.draw(tText);
	for (auto e : vButten)
		e->draw(target);
}
//Funktionen zum �berp�fen der Maus und �ndern der Farbe
	//Buttens
int Kachel::checkButtenishover(sf::Vector2i mouspos)
{
	for (int i = 0; i < vButten.size(); i++)
	{
		if (vButten[i]->isHover(mouspos))
		{
			vButten[i]->setHoverColor();
			return vButten[i]->getID();
		}
	}
	return 99;
}

bool Kachel::checkButtenisPressed(int ButtenID, sf::Vector2i mouspos)
{
	for (int i = 0; i < vButten.size(); i++)
	{
		if (vButten[i]->getID() == ButtenID)
		{
			if (vButten[i]->isPressed(mouspos))
			{
				vButten[i]->setPressColor();
				return true;
			}
		}
	}
	return false;
}

 void Kachel::setButtenColorToNormal()
{
	for (auto e : vButten)
		e->setNormalColor();
}
//Kachel
bool Kachel::ishover(sf::Vector2i mouspos)
{
	if (mouspos.x > kachel.getPosition().x && mouspos.x<kachel.getPosition().x + kachel.getGlobalBounds().width &&
		mouspos.y>kachel.getGlobalBounds().top && mouspos.y < kachel.getGlobalBounds().top + kachel.getGlobalBounds().height)
		return true;
	return false;
}

bool Kachel::isPressed(sf::Vector2i mouspos)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true && bdruken == false) //sfTimer.getElapsedTime().asMilliseconds() > 400)
	{
		bdruken = true;
		return true;
	}

	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		bdruken = false;

	return false;
}

 void Kachel::sethoverColor()
{
	kachel.setFillColor(sfHoverColor);
}

 void Kachel::setPressedColor()
{
	kachel.setFillColor(sfPressColor);
}

 void Kachel::setNormalColor()
{
	kachel.setFillColor(sfBackroundColor);
}
 int Kachel::getID()
 {
	 return iID;
 }
//Privat Functions
void Kachel::newText(std::string Text, int PosTextY)
{
	tText.setString(Text);
	tText.setPosition(
		kachel.getPosition().x + ((kachel.getGlobalBounds().width / 2.f) - (tText.getGlobalBounds().width / 2.f)),
		PosTextY
	);
}
