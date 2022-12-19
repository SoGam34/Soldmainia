#include "Kachel.h"

//Konstruktoren#include "stdafx.h"
Kachel::Kachel()
{
	bdruken = false;
	PressTimer = 0;
	//Butten
	vButten.clear();
}

Kachel::Kachel(std::string Text, int PosTextY, sf::Color TextColor, sf::Font* font,
	int IDTexture, int PosTextureX, int PosTextureY, 
	int ID, int PosKachelX, int PosKachelY, float with, float height,
	sf::Color backroundColor, sf::Color hoverColor, sf::Color pressColor)
{
	// Texture
	iIDTexture = IDTexture;
	TexturePos.x = PosTextureX;
	TexturePos.y = PosTextureY;
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
	PressTimer = 0;
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
							sf::Color backroundColor, sf::Color hoverColor, sf::Color PressColor, sf::Color textColor,
							float KachelBreite, float KachelHohe)
{
	vButten.push_back(new Butten(x, y, with, heigth, ID, text, font, backroundColor, hoverColor, PressColor, textColor, KachelBreite, KachelHohe));
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
	TexturePos.x = PosTextureX;
	TexturePos.y = PosTextureY;
}

void Kachel::changeText(std::string Text, int PosTextY)
{
	newText(Text, PosTextY);
}

void Kachel::drawFenster(sf::RenderTarget& target)
{
	target.draw(kachel);
	for (auto e : vButten)
		e->drawFenster(target);
}

void Kachel::drawText(sf::RenderTarget& target)
{
	target.draw(tText);
	for (auto e : vButten)
		e->drawText(target);
}
//Funktionen zum Überpüfen der Maus und ändern der Farbe
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

 void Kachel::updatePos(int PosX, int PosY, int breite, int hohe)
 {
	 int tempx = PosX - kachel.getPosition().x;
	 
	 int tempy = PosY - kachel.getPosition().y ;
	 
	 for (auto e : vButten)
	 {
		 e->updatePos(tempx, tempy*2, breite, hohe);
	 }
	 
	 TexturePos += sf::Vector2f(tempx, tempy);

	 kachel.setPosition(PosX, PosY);
	 kachel.setSize(sf::Vector2f(breite, hohe));

	 tText.setPosition(
		 kachel.getPosition().x + ((kachel.getGlobalBounds().width / 2.f) - (tText.getGlobalBounds().width / 2.f)),
		 tText.getPosition().y
	 );
 }

 void Kachel::update()
 {
	 if (PressTimer > 0)
		 PressTimer--;

	 if (PressTimer != 0)
		 kachel.setFillColor(sfPressColor);

	 for (auto e : vButten)
		 e->update();
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
	 if (PressTimer == 0)
	 {
		 kachel.setFillColor(sfHoverColor);
	 }
}

 void Kachel::setPressedColor()
{
	PressTimer = 15;
	kachel.setFillColor(sfPressColor);
}

 void Kachel::setNormalColor()
{
	 if (PressTimer == 0)
	 {
		 kachel.setFillColor(sfBackroundColor);
	 }
}
 int Kachel::getID()
 {
	 return iID;
 }
 int Kachel::getTextureID()
 {
	 return iIDTexture;
 }
 sf::Vector2f Kachel::getTexturePosition()
 {
	 return TexturePos;
 }
 sf::Vector2f Kachel::getPos()
 {
	 return kachel.getPosition();
 }
 sf::Vector2f Kachel::getSize()
 {
	 return kachel.getSize();
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
