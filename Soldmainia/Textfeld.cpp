#include "Textfeld.h"

Textfeld::Textfeld()
{

}

Textfeld::Textfeld(sf::Color farbe, sf::Font *font, sf::Vector2f pos)
{
	tTextfeld.setFillColor(farbe);
	tTextfeld.setCharacterSize(15);
	tTextfeld.setFont(*font);
	tTextfeld.setPosition(pos);

	setAusgewahlt(true);
}

bool Textfeld::checkEnter(sf::Event event)
{
	if (event.text.unicode == ENTER_KEY)
	{
		bAusgewalt = true;
		return true;
	}

	return false;
}
void Textfeld::Typing(sf::Event event)
{
	int Buchstabe = event.text.unicode;
	if (Buchstabe < 128&&Buchstabe>=0)
	{
		inputlogic(Buchstabe);
	}
}

bool Textfeld::getAusgewahlt()
{
	return bAusgewalt;
}

void Textfeld::setAusgewahlt(bool auswahl)
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
		tTextfeld.setString(oText.str());
	}

	else
	{
		tTextfeld.setString(oText.str()+"_");
	}
}

void Textfeld::drawText(sf::RenderTarget& target)
{
	target.draw(tTextfeld);
}

void Textfeld::inputlogic(int Buch)
{
	if (Buch != DELETE_KEY && Buch != ESCAPE_KEY && Buch != ENTER_KEY)
	{
		oText << static_cast<char>(Buch);
		tTextfeld.setString(oText.str() + "_");
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
			tTextfeld.setString(oText.str()+"_");
		}
	}

	else if (Buch == ESCAPE_KEY)
		setAusgewahlt(false);

	else if (Buch == ENTER_KEY)
		setAusgewahlt(true);
}

sf::Vector2f Textfeld::getPos()
{
	return tTextfeld.getPosition();
}

sf::FloatRect Textfeld::getBounds()
{
	return tTextfeld.getGlobalBounds();
}

std::string Textfeld::getText()
{
	return oText.str();
}