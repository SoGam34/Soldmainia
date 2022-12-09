#pragma once
#include "Butten.h"

class Kachel
{
public:
	//Konstruktoren
	Kachel();
	Kachel(std::string Text, int PosTextY, sf::Color TextColor, sf::Font* font,
		int IDTexture, int PosTextureX, int PosTextureY,
		int ID, int PosKachelX, int PosKachelY, float with, float height,
		sf::Color backroundColor, sf::Color hoverColor, sf::Color pressColor);
	~Kachel();
	//Funktionen zum dieseignen und Mahlen der Kachel
	 void addButten(float x, float y, float with, float heigth, int ID,
						std::string text, sf::Font* font,
						sf::Color backroundColor, sf::Color hoverColor, sf::Color PressColor, sf::Color textColor);

	void neuesBild(std::string Text, int PosTextY, 
				int IDTexture, int PosTextureX, int PosTextureY);

	void changeText(std::string Text, int PosTextY);

	void drawFenster(sf::RenderTarget& target);
	
	void drawText(sf::RenderTarget& target);
	//Funktionen zum Überpüfen der Maus und ändern der Farbe
	//Buttens
	int checkButtenishover(sf::Vector2i mouspos);

	bool checkButtenisPressed(int ButtenID, sf::Vector2i mouspos);

	 void setButtenColorToNormal();
	//Kachel
	bool ishover(sf::Vector2i mouspos);

	bool isPressed(sf::Vector2i mouspos);

	void sethoverColor();

	void setPressedColor();

	void setNormalColor();

	void setSize(sf::Vector2f posKachel, sf::Vector2f posTex, sf::Vector2f size);

	void setScale(float sice);

	int getID();
	
	int getTextureID();

	float getScale();
	
	sf::Vector2f getTexturePosition();

	void setTexturePosition(sf::Vector2f pos);
	
private:
	//Kachel
	sf::RectangleShape kachel;
	sf::Text tText;
	sf::Color sfBackroundColor, sfHoverColor, sfPressColor;
	bool bdruken;
	int iID;
	void newText(std::string Text, int PosTextY);
	//Texture
	int iIDTexture;
	sf::Vector2f TexturePos;
	float TextureScale;
	//Butten
	std::vector <Butten*> vButten;
	int iButtenZähler;
};

