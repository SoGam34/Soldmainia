#include "PreHeader.h"
#include "Textfeld.h"

Textfeld::Textfeld(const sf::Color farbe, const sf::Font& font, const sf::Vector2f pos)
{
	sf_tTextfeld.setFillColor(farbe);
	sf_tTextfeld.setCharacterSize(15);
	sf_tTextfeld.setFont(font);
	sf_tTextfeld.setPosition(pos);

	setTextfeldAusgewahlt(true);
}

Textfeld::~Textfeld()
{
}

bool Textfeld::ueberpruefeObEnterGedrueckt(const sf::Event& event)
{
	if (event.text.unicode == ENTER_KEY)
	{
		bAusgewalt = true;
		return true;
	}

	return false;
}
void Textfeld::BuchstabeGedrückt(const sf::Event& event)
{
	int Buchstabe = event.text.unicode;
	if (Buchstabe < 128&&Buchstabe>=0)
	{
		inputlogic(Buchstabe);
	}
}

const inline bool Textfeld::getAusgewahlt() const
{
	return bAusgewalt;
}

void Textfeld::setTextfeldAusgewahlt(bool auswahl)
{
	bAusgewalt = auswahl;
	if (!auswahl)
	{
		std::string newText;
		for (int i = 0; i < oText.str().length(); i++)
		{
			newText += oText.str()[i];
		}
		oText.str("");
		oText << newText;
		sf_tTextfeld.setString(oText.str());
	}

	else
	{
		sf_tTextfeld.setString(oText.str()+"_");
	}
}

void Textfeld::drawText(sf::RenderTarget& target)
{
	target.draw(sf_tTextfeld);
}

void Textfeld::inputlogic(int Buch)
{
	if (Buch != DELETE_KEY && Buch != ESCAPE_KEY && Buch != ENTER_KEY)
	{
		oText << static_cast<char>(Buch);
		sf_tTextfeld.setString(oText.str() + "_");
	}

	else if (Buch == DELETE_KEY)
	{
		if (oText.str().length() > 0)
		{
			std::string newText;
			for (int i = 0; i < oText.str().length() - 1; i++)
			{
				newText += oText.str()[i];
			}
			oText.str("");
			oText << newText;
			sf_tTextfeld.setString(oText.str()+"_");
		}
	}

	else if (Buch == ESCAPE_KEY)
		setTextfeldAusgewahlt(false);

	else if (Buch == ENTER_KEY)
		setTextfeldAusgewahlt(true);
}

const inline sf::Vector2f Textfeld::getPosition() const
{
	return sf_tTextfeld.getPosition();
}

const inline sf::FloatRect Textfeld::getBegrenzungen() const
{
	return sf_tTextfeld.getGlobalBounds();
}

const inline std::string Textfeld::getText() const
{
	return oText.str();
}