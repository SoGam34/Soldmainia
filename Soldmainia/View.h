#pragma once
#include "Data.h"

class View 
{
public:
	//De/Konstrucktor
	View();
	View(Data* data);
	~View();
	
	void DrawHauptmenu(int iTage);
	void DrawBAZ(int iTage);
	void DrawScoutbuero(int iTage);

	sf::Vector2i getMousPos();
	bool windowOpen();
	void Close();

private:
	void drawFenster(int start, int range);
	void drawSprite(int start, int range);
	void drawText(int start, int range, std::string titel, int iTag);
	
	//window
	sf::RenderWindow* window;

	// Data zeiger
	Data* cData;				 
	
	sf::Texture tTexture;
	sf::Sprite sSprite;
	
	std::string Addressen[15]
	{
		"Texturen/Pfeil.png",
		"Texturen/Haken.png"
	};
	sf::Text sfText;
};