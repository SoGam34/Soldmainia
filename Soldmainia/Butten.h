#pragma once
#include "pch.h"

class Butten
{
public:
	//Konstruktoren
	Butten();
	Butten(float x, float y, float with, float heigth, int ID,
		std::string text, sf::Font* font,
		sf::Color backroundColor, sf::Color hoverColor, sf::Color PressColor, sf::Color textColor);
	~Butten();

	//�berprufen ob die Maus sich �ber dem Butten befindet und dieser gedr�ckt wird
	bool isPressed(sf::Vector2i mouspos);
	bool isHover(sf::Vector2i mouspos);
	void update();
	//�ndern die Farbe des Butten
	 void setPressColor();
	 void setHoverColor();
	 void setNormalColor();
	//Get/Set Funktion
	 int getID();

	void drawFenster(sf::RenderTarget& target);
	void drawText(sf::RenderTarget& target);

private:
	sf::RectangleShape butten;
	sf::Text tText;
	sf::Color sfBackroundColor, sfHoverColor, sfPressColor;
	//sf::Clock sfTimer;
	int iID;
	bool bdruken;
	int PressTimer;
};

