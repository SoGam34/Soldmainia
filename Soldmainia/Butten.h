#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <vector>
#include <iostream>
#include <time.h>
#include <sstream>

class Butten
{
public:
	//Konstruktoren
	Butten();
	Butten(float x, float y, float with, float heigth, int ID,
		std::string text, sf::Font* font,
		sf::Color backroundColor, sf::Color hoverColor, sf::Color PressColor, sf::Color textColor,
		float KachelBreite, float KachelHohe);
	~Butten();

	//ueberprufen ob die Maus sich ueber dem Butten befindet und dieser gedrueckt wird
	bool isPressed(sf::Vector2i mouspos);
	bool isHover(sf::Vector2i mouspos);
	void update();
	void updatePos(int PosX, int PosY, int breite, int hohe);
	//aendern die Farbe des Butten
	 void setPressColor();
	 void setHoverColor();
	 void setNormalColor();
	//Get/Set Funktion
	 int getID();

	 sf::Vector2f getPos();

	 sf::Vector2f getSize();
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

	float factorBreite;
	float factorHohe;
};

