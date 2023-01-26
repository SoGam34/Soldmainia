#include "PreHeader.h"
#include "Butten.h"



Button::Button(float Button_x, float Button_y, float Button_Breite, float Button_Hohe, unsigned int Button_ID, std::string Button_Text, sf::Font& font, sf::Color backroundColor, sf::Color hoverColor, sf::Color PressColor, sf::Color textColor, float KachelBreite, float KachelHohe)
{
	sf_rsButton.setPosition(Button_x, Button_y);
	sf_rsButton.setSize(sf::Vector2f(Button_Breite, Button_Hohe));
	sf_rsButton.setFillColor(backroundColor);

	sf_tText.setFont(font);
	sf_tText.setCharacterSize(15);
	sf_tText.setString(Button_Text);
	sf_tText.setPosition(
		sf_rsButton.getPosition().x + ((sf_rsButton.getGlobalBounds().width / 2) - (sf_tText.getGlobalBounds().width / 2)),
		sf_rsButton.getPosition().y + ((sf_rsButton.getGlobalBounds().height / 2) - (sf_tText.getGlobalBounds().height / 2))
	);
	sf_tText.setFillColor(textColor);

	sf_cHintergrundfarbe = backroundColor;
	sf_cSchwebefarbe = hoverColor;
	sf_cGedrücktfarbe = PressColor;
	iID = Button_ID;
	bDruecken = false;
	iVerbleibendeDrueckZeit = 0;

	fFactorBreite = Button_Breite / KachelBreite;
	fFactorHohe = Button_Hohe / KachelHohe;
}

Button::~Button()
{

}

bool Button::wirdGedrückt()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true && bDruecken==false ) 
	{
		bDruecken = true;
		return true;
	}

	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		bDruecken = false;
	
	return false;
}

bool Button::MausSchwebtDrüber(const sf::Vector2i& mouspos)
{
	if (mouspos.x > sf_rsButton.getPosition().x && mouspos.x<sf_rsButton.getPosition().x + sf_rsButton.getGlobalBounds().width &&
		mouspos.y>sf_rsButton.getGlobalBounds().top && mouspos.y < sf_rsButton.getGlobalBounds().top + sf_rsButton.getGlobalBounds().height)
		return true;
	return false;
}

void Button::aktualisieren()
{
	if (iVerbleibendeDrueckZeit > 0)
		iVerbleibendeDrueckZeit--;
	
	if (iVerbleibendeDrueckZeit != 0)
		sf_rsButton.setFillColor(sf_cGedrücktfarbe);
}

void Button::aktualisierenPosition(float Button_x, float Button_y, float Button_Breite, float Button_Hohe)
{
	sf_rsButton.setPosition(sf_rsButton.getPosition().x + Button_x,
		sf_rsButton.getPosition().y + Button_y);

	sf_rsButton.setSize(sf::Vector2f(Button_Breite * fFactorBreite, ((Button_Hohe * fFactorHohe)>45)?45: (Button_Hohe * fFactorHohe)));

	sf_tText.setPosition(
		sf_rsButton.getPosition().x + ((sf_rsButton.getGlobalBounds().width / 2) - (sf_tText.getGlobalBounds().width / 2)),
		sf_rsButton.getPosition().y + ((sf_rsButton.getGlobalBounds().height / 2) - (sf_tText.getGlobalBounds().height / 2))
	);
}

const inline void Button::setButton_Gedrücktfarbe()
{
	iVerbleibendeDrueckZeit = 15;
	sf_rsButton.setFillColor(sf_cGedrücktfarbe);
}

const inline void Button::setButton_Schwebefarbe()
{
	if (iVerbleibendeDrueckZeit == 0)
	{
		sf_rsButton.setFillColor(sf_cSchwebefarbe);
	}
}

const inline void Button::setButton_Hintergrundfarbe()
{
	if (iVerbleibendeDrueckZeit == 0)
	{
		sf_rsButton.setFillColor(sf_cHintergrundfarbe);
	}
}

const inline unsigned int Button::getID() const
{
	return iID;
}

const inline sf::Vector2f Button::getPosition() const
{
	return sf_rsButton.getPosition();
}

const inline sf::Vector2f Button::getGroese() const
{
	return sf_rsButton.getSize();
}

void Button::drawFenster(sf::RenderTarget& target)
{
	target.draw(sf_rsButton);
}

void Button::drawText(sf::RenderTarget& target)
{
	target.draw(sf_tText);
}
