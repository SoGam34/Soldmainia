#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textfeld
{
public:
	Textfeld();
	Textfeld(sf::Color farbe, sf::Font *font, sf::Vector2f pos);

	bool checkEnter(sf::Event event);

	void Typing(sf::Event event);

	bool getAusgewahlt();
	void setAusgewahlt(bool auswahl);

	sf::Vector2f getPos();
	sf::FloatRect getBounds();

	std::string getText();

	void drawText(sf::RenderTarget& target);
private:
	sf::Text tTextfeld;
	std::ostringstream oText;
	bool bAusgewalt;

	void inputlogic(int Buch);
};

