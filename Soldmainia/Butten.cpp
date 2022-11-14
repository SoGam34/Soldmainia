#include "Butten.h"

Butten::Butten()
{
	iID = 99;
}

Butten::Butten(	float x, float y, float with, float heigth, int ID,
				std::string text, sf::Font* font, 
				sf::Color backroundColor, sf::Color hoverColor, sf::Color PressColor, sf::Color textColor)
{
	butten.setPosition(x, y);
	butten.setSize(sf::Vector2f(with, heigth));
	butten.setFillColor(backroundColor);

	tText.setFont(*font);
	tText.setCharacterSize(15);
	tText.setString(text);
	tText.setPosition(
		butten.getPosition().x + ((butten.getGlobalBounds().width / 2) - (tText.getGlobalBounds().width / 2)),
		butten.getPosition().y + ((butten.getGlobalBounds().height / 2) - (tText.getGlobalBounds().height / 2))
	);
	tText.setFillColor(textColor);

	sfBackroundColor = backroundColor;
	sfHoverColor = hoverColor;
	sfPressColor = PressColor;
	iID = ID;
	bdruken = false;
}

Butten::~Butten()
{
}

bool Butten::isPressed(sf::Vector2i mouspos)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true && bdruken==false ) //sfTimer.getElapsedTime().asMilliseconds() > 400)
	{
		//sfTimer.restart();
		bdruken = true;
		return true;
	}

	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		bdruken = false;
	
	return false;
}

bool Butten::isHover(sf::Vector2i mouspos)
{
	if (mouspos.x > butten.getPosition().x && mouspos.x<butten.getPosition().x + butten.getGlobalBounds().width &&
		mouspos.y>butten.getGlobalBounds().top && mouspos.y < butten.getGlobalBounds().top + butten.getGlobalBounds().height)
		return true;
	return false;
}

void Butten::setPressColor()
{
	butten.setFillColor(sfPressColor);
}

void Butten::setHoverColor()
{
	butten.setFillColor(sfHoverColor);
}

void Butten::setNormalColor()
{
	butten.setFillColor(sfBackroundColor);
}

int Butten::getID()
{
	return iID;
}

void Butten::drawFenster(sf::RenderTarget& target)
{
	target.draw(butten);
}

void Butten::drawText(sf::RenderTarget& target)
{
	target.draw(tText);
}
