#include "PreHeader.h"
#include "Butten.h"



Button::Button(float Button_x, float Button_y, float Button_Breite, float Button_Hohe, unsigned int Button_ID,
	std::string Button_Text, sf::Font& font,
	sf::Color Button_Hintergrundfarbe, sf::Color Button_Schwebefarbe, sf::Color Button_Gedruecktfarbe, sf::Color Button_Textfarbe,
	float Kachel_Breite, float Kachel_Hohe)
 :  sf_cHintergrundfarbe(Button_Hintergrundfarbe),
	sf_cSchwebefarbe(Button_Schwebefarbe),
	sf_cGedruecktfarbe(Button_Gedruecktfarbe),
	iID(Button_ID),
	bDruecken(false),
	iVerbleibendeDrueckZeit(0)
{
	sf_rsButton.setPosition(Button_x, Button_y);
	sf_rsButton.setSize(sf::Vector2f(Button_Breite, Button_Hohe));
	sf_rsButton.setFillColor(sf_cHintergrundfarbe);

	sf_tText.setFont(font);
	sf_tText.setCharacterSize(15);
	sf_tText.setString(Button_Text);
	sf_tText.setPosition(
		sf_rsButton.getPosition().x + ((sf_rsButton.getGlobalBounds().width / 2) - (sf_tText.getGlobalBounds().width / 2)),
		sf_rsButton.getPosition().y + ((sf_rsButton.getGlobalBounds().height / 2) - (sf_tText.getGlobalBounds().height / 2))
	);
	sf_tText.setFillColor(Button_Textfarbe);

	fFactorBreite = Button_Breite / Kachel_Breite;
	fFactorHohe = Button_Hohe / Kachel_Hohe;
}

Button::~Button()
{

}

bool Button::wirdGedrueckt()
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

bool Button::MausSchwebtDrueber(const sf::Vector2i& mouspos)
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
		sf_rsButton.setFillColor(sf_cGedruecktfarbe);
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

const  void Button::setButton_Gedruecktfarbe()
{
	iVerbleibendeDrueckZeit = 15;
	sf_rsButton.setFillColor(sf_cGedruecktfarbe);
}

const  void Button::setButton_Schwebefarbe()
{
	if (iVerbleibendeDrueckZeit == 0)
	{
		sf_rsButton.setFillColor(sf_cSchwebefarbe);
	}
}

const  void Button::setButton_Hintergrundfarbe()
{
	if (iVerbleibendeDrueckZeit == 0)
	{
		sf_rsButton.setFillColor(sf_cHintergrundfarbe);
	}
}

const  unsigned int Button::getID() const
{
	return iID;
}

const  sf::Vector2f Button::getPosition() const
{
	return sf_rsButton.getPosition();
}

const  sf::Vector2f Button::getGroese() const
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
